#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

// A simple function to be registered in the Janet environment
static Janet cfun_add(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    if (!janet_checktype(argv[0], JANET_NUMBER) || !janet_checktype(argv[1], JANET_NUMBER)) {
        janet_panic("expected two numbers");
    }
    double x = janet_unwrap_number(argv[0]);
    double y = janet_unwrap_number(argv[1]);
    return janet_wrap_number(x + y);
}

int LLVMFuzzerTestOneInput_1268(const uint8_t *data, size_t size) {
    // Initialize Janet environment
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Ensure the data is null-terminated for use as a string
    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        janet_deinit();
        return 0;
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Create a JanetRegExt array with a simple function
    JanetRegExt regext[] = {
        {"add", cfun_add, NULL, NULL},  // Register a simple add function
        {NULL, NULL, NULL, NULL}        // End of array
    };

    // Register the function in the Janet environment
    janet_cfuns_ext(table, cstr, regext);

    // Prepare arguments for the function call
    if (size >= 2 * sizeof(double)) {
        double num1, num2;
        memcpy(&num1, data, sizeof(double));
        memcpy(&num2, data + sizeof(double), sizeof(double));

        // Wrap the numbers as Janet values
        Janet argv[2];
        argv[0] = janet_wrap_number(num1);
        argv[1] = janet_wrap_number(num2);

        // Call the registered function
        Janet result = cfun_add(2, argv);
        (void)result; // Use the result to avoid unused variable warning
    }

    // Clean up
    free(cstr);
    janet_deinit();

    return 0;
}