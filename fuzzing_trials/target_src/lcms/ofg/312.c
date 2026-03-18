#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_312(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    cmsMLU *mlu = cmsMLUalloc(NULL, 1);
    const char *language = "en";
    const char *country = "US";
    char *text = NULL;

    // Ensure size is not zero to avoid allocating zero bytes
    if (size > 0) {
        // Allocate memory for text and copy data into it
        text = (char *)malloc(size + 1);
        if (text != NULL) {
            memcpy(text, data, size);
            text[size] = '\0'; // Null-terminate the string
        }
    }

    // Call the function-under-test
    if (mlu != NULL && text != NULL) {
        cmsMLUsetUTF8(mlu, language, country, text);
    }

    // Free allocated resources
    if (mlu != NULL) {
        cmsMLUfree(mlu);
    }
    if (text != NULL) {
        free(text);
    }

    return 0;
}