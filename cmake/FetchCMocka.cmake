include(FetchContent)

FetchContent_Declare(
  cmocka
  GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
  GIT_TAG        cmocka-1.1.5
  GIT_SHALLOW    1
)

option(WITH_EXAMPLES OFF)
set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)

FetchContent_MakeAvailable(cmocka)
