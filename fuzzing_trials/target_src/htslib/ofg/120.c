#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>

// Declare the fuzzing function without 'extern "C"' as this is C code
int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for hts_opt pointer
    hts_opt *opt = NULL;

    // Create a null-terminated string from the input data
    char *opt_string = (char *)malloc(size + 1);
    if (opt_string == NULL) {
        return 0;
    }
    memcpy(opt_string, data, size);
    opt_string[size] = '\0';

    // Call the function-under-test
    int result = hts_opt_add(&opt, opt_string);

    // Free allocated memory
    free(opt_string);

    // Clean up hts_opt if necessary
    if (opt != NULL) {
        hts_opt_free(opt);
    }

    return 0;
}