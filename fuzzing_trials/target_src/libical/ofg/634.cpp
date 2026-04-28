#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_634(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_XLICMIMECHARSET_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Allocate memory for the charset string and copy data into it
    char *charset = (char *)malloc(size + 1);
    if (charset == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(charset, data, size);
    charset[size] = '\0';  // Null-terminate the string

    // Call the function under test
    icalproperty_set_xlicmimecharset(prop, charset);

    // Additional checks to increase code coverage
    const char *retrieved_charset = icalproperty_get_xlicmimecharset(prop);
    if (retrieved_charset != NULL) {
        // Simulate some processing or validation
        if (strcmp(retrieved_charset, charset) == 0) {
            // Further processing can be added here
            // For example, we can manipulate the property further to ensure more code paths are tested
            icalproperty_set_xlicmimecharset(prop, "test-charset");
            const char *new_charset = icalproperty_get_xlicmimecharset(prop);
            if (new_charset != NULL && strcmp(new_charset, "test-charset") == 0) {
                // Additional validation or processing
            }
        }
    }

    // Test with edge cases by setting an empty charset
    icalproperty_set_xlicmimecharset(prop, "");
    const char *empty_charset = icalproperty_get_xlicmimecharset(prop);
    if (empty_charset != NULL && strcmp(empty_charset, "") == 0) {
        // Additional validation or processing for empty charset
    }

    // Test with a very large charset
    char *large_charset = (char *)malloc(10000);
    if (large_charset != NULL) {
        memset(large_charset, 'A', 9999);
        large_charset[9999] = '\0';
        icalproperty_set_xlicmimecharset(prop, large_charset);
        const char *retrieved_large_charset = icalproperty_get_xlicmimecharset(prop);
        if (retrieved_large_charset != NULL) {
            // Additional validation or processing for large charset
        }
        free(large_charset);
    }

    // Clean up
    free(charset);
    icalproperty_free(prop);

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

    LLVMFuzzerTestOneInput_634(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
