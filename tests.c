#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int add(int a, int b) {
    return a+b;
}

void add_test(void) {
    CU_ASSERT(add(1,2) == 3);
    CU_ASSERT(add(314,232) == 546);
}