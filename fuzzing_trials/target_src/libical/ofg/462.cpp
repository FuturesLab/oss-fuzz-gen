#include <cstdint>  // For uint8_t
#include <cstdlib>  // For malloc and free
#include <cstring>  // For memcpy
#include <cctype>   // For isalnum

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_462(const uint8_t *data, size_t size) {
    // Ensure the data is non-empty for string operations
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the string and ensure it's null-terminated
    char *mime_encoding = (char *)malloc(size + 1);
    if (mime_encoding == NULL) {
        return 0;
    }
    memcpy(mime_encoding, data, size);
    mime_encoding[size] = '\0';

    // Validate the input to ensure it's a valid MIME encoding
    // For the sake of this example, let's assume valid MIME encodings are alphanumeric
    for (size_t i = 0; i < size; ++i) {
        if (!isalnum(mime_encoding[i]) && mime_encoding[i] != '-') {
            free(mime_encoding);
            return 0;
        }
    }

    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_XLICMIMEENCODING_PROPERTY);
    if (prop == NULL) {
        free(mime_encoding);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_xlicmimeencoding(prop, mime_encoding);

    // Additional operations to ensure code coverage
    // Retrieve the value to ensure the set operation was successful
    const char *retrieved_mime_encoding = icalproperty_get_xlicmimeencoding(prop);
    if (retrieved_mime_encoding != NULL) {
        // Optionally, perform operations with the retrieved value
        // For example, compare it with the original input
        if (strcmp(mime_encoding, retrieved_mime_encoding) != 0) {
            // Handle mismatch if needed
        }
    }

    // Clean up
    icalproperty_free(prop);
    free(mime_encoding);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_462(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
