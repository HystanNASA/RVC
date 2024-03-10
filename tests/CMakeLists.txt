file(GLOB TEST_SOURCES
	main.c
)

add_executable(rvc_unittests ${TEST_SOURCES})
target_link_libraries(rvc_unittests PRIVATE cmocka-static)

enable_testing()
add_test(NAME rvc_unittests COMMAND rvc_unittests)
