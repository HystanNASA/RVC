#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void true_test(void **state)
{
	assert_true(1 == 1);
}

int main()
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(true_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
