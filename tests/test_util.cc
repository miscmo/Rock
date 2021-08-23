#include "rock/rock.h"
#include <assert.h>

rock::Logger::ptr g_logger = ROCK_LOG_ROOT();

void test_assert() {
    ROCK_LOG_INFO(g_logger) << rock::BacktraceToString(10);
    //ROCK_ASSERT2(0 == 1, "abcdef xx");
}

int main(int argc, char** argv) {
    test_assert();

    int arr[] = {1,3,5,7,9,11};

    ROCK_LOG_INFO(g_logger) << rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 0);
    ROCK_LOG_INFO(g_logger) << rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 1);
    ROCK_LOG_INFO(g_logger) << rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 4);
    ROCK_LOG_INFO(g_logger) << rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 13);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 0) == -1);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 1) == 0);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 2) == -2);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 3) == 1);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 4) == -3);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 5) == 2);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 6) == -4);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 7) == 3);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 8) == -5);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 9) == 4);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 10) == -6);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 11) == 5);
    ROCK_ASSERT(rock::BinarySearch(arr, sizeof(arr) / sizeof(arr[0]), 12) == -7);
    return 0;
}
