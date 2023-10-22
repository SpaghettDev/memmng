# memmng

Memory manager. Basically std::any but made in like a day lol.

# Build (why?)
1. `git clone https://github.com/SpaghettDev/memmng`
2. `cd memmng`
3. `mkdir build`
4. `cd build`
5. `cmake ..`
6. Open generated solution

# Add to a cmake project (why?)
```cmake
include(FetchContent)

FetchContent_Declare(
    memmng
    GIT_REPOSITORY https://github.com/SpaghettDev/memmng.git
    GIT_TAG        43ca0f5ed326ad3d72e54db2248912f7c4f251bf
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(memmng)
set_property(TARGET memmng PROPERTY CXX_STANDARD 20)
```
