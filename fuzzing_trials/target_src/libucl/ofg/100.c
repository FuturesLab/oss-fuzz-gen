#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Initialize a ucl_object_iter_t variable
    ucl_object_iter_t *iter = (ucl_object_iter_t *)malloc(sizeof(ucl_object_iter_t));

    // Ensure the iterator is not NULL
    if (iter == NULL) {
        return 0;
    }

    // Initialize the iterator with some data to avoid NULL dereference
    *iter = (ucl_object_iter_t)data; // Cast data to ucl_object_iter_t type

    // Call the function-under-test
    bool result = ucl_object_iter_chk_excpn(iter);

    // Free the allocated memory for the iterator
    free(iter);

    return 0;
}