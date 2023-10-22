#include <cstddef>
#include <cstdlib>
#include <format>
#include <type_traits>
#include <exception>

// exceptions
class bad_cast : public std::exception
{
public:
	bad_cast(int target_size, int allocated_size)
		: m_target_size(target_size), m_allocated_size(allocated_size)
	{};

	const char* what() const noexcept override
	{
		std::string s = std::format("Target type size ({}) is larger than allocated size ({}).", m_target_size, m_allocated_size);
		const char* cs = s.c_str();

		return cs;
	};

private:
	int m_target_size;
	int m_allocated_size;
};

class bad_resize : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Cannot resize memmng data in safe mode.";
	};
};


/*
	Automatically managed raw heap memory
*/
template<std::size_t S, bool SAFE = true>
class memmng
{
public:
	memmng()
	{
		m_data = std::malloc(S);

		if (m_data == nullptr)
			throw std::bad_alloc();
	}

	~memmng()
	{
		std::free(m_data);
	}

	template<typename T>
	T as() const noexcept(!SAFE || (sizeof(T) <= S))
	{
		if constexpr (SAFE && sizeof(T) > S)
			throw bad_cast(sizeof(T), S);

		// TODO: std::bit_cast
		return *reinterpret_cast<T*>(m_data);
	}

	template<typename T>
	void set(T value) noexcept(!SAFE || (sizeof(T) <= S))
	{
		if constexpr (SAFE && sizeof(T) > S)
			throw bad_cast(sizeof(T), S);

		*reinterpret_cast<T*>(m_data) = value;
	}

	template<std::size_t NS, bool U = SAFE>
	typename std::enable_if<U>::type* resize() = delete;
	
	template<std::size_t NS, bool U = SAFE>
	[[maybe_unused]] typename std::enable_if<!U>::type* resize()
	{
		m_data = std::realloc(m_data, NS);

		if (m_data == nullptr)
			throw std::bad_alloc();

		m_nsize = NS;

		return m_data;
	}

	template<bool U = SAFE>
	constexpr std::enable_if<U, std::size_t>::type size() const noexcept
	{
		return S;
	}

	template<bool U = SAFE>
	std::enable_if<!U, std::size_t>::type size() const noexcept
	{
		return m_nsize;
	}

	template<typename T>
	void operator=(T value) noexcept(!SAFE || (sizeof(T) <= S))
	{
		set(value);
	}

	memmng& operator=(const memmng&) = delete;
	static void* operator new(std::size_t) = delete;

private:
	void* m_data;
	std::size_t m_nsize;
};
