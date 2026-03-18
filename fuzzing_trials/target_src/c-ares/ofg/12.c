#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <ares.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    /* Extract an integer code from the input data */
    int code = *(const int*)data;

    /* Call the function-under-test */
    const char *error_message = ares_strerror(code);

    /* Print the error message for debugging purposes */
    if (error_message != NULL) {
        printf("Error message: %s\n", error_message);
    }

    return 0;
}