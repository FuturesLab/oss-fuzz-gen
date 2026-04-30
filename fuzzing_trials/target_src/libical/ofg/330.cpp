#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_330(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the string and ensure it's null-terminated
    char *charset = (char *)malloc(size + 1);
    if (charset == nullptr) {
        return 0;
    }

    memcpy(charset, data, size);
    charset[size] = '\0';

    // Create a dummy icalproperty to ensure the function is meaningfully invoked
    icalproperty *dummy_prop = icalproperty_new_xlicerror("Dummy error");

    // Call the function-under-test with more context
    icalproperty *prop = icalproperty_vanew_xlicmimecharset(charset, dummy_prop, nullptr);

    // Check if the property was created successfully and perform additional operations
    if (prop != nullptr) {
        // Attempt to retrieve and print some property values to ensure proper invocation
        const char *retrieved_charset = icalproperty_get_xlicmimecharset(prop);
        
        // Optionally, perform some checks or operations on retrieved_charset
        if (retrieved_charset != nullptr) {
            // Dummy operation to ensure the value is used
            printf("Retrieved charset: %s\n", retrieved_charset);
        }

        // Free the property
        icalproperty_free(prop);
    }

    // Free the dummy property
    if (dummy_prop != nullptr) {
        icalproperty_free(dummy_prop);
    }
    
    // Free the allocated charset
    free(charset);

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

    LLVMFuzzerTestOneInput_330(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
