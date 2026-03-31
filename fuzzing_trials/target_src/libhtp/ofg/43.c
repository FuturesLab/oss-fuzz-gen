#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Include ctype.h for toupper
#include "/src/libhtp/htp/bstr.h" // Correct path for bstr.h

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to be used as a C string
    if (size == 0) {
        return 0;
    }

    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        return 0;
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Call the function-under-test
    bstr *result = bstr_wrap_c(cstr);

    if (result != NULL) {
        // Perform additional operations on the bstr object to increase coverage
        size_t len = bstr_len(result);
        if (len > 0) {
            // Example operation: Convert to uppercase
            for (size_t i = 0; i < len; i++) {
                result->realptr[i] = toupper(result->realptr[i]);
            }
        }

        // Assuming there is a function to free bstr objects
        bstr_free(result);
    }

    // Clean up
    free(cstr);

    return 0;
}