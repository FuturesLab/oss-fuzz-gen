#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1067(const uint8_t *data, size_t size) {
    // Ensure the input size is non-zero and reasonable for creating a valid C-string.
    if (size == 0 || size > 1000) return 0; // Limit size to prevent excessive memory usage

    // Allocate memory for the C-string and ensure it's null-terminated.
    char *input = static_cast<char*>(malloc(size + 1));
    if (input == nullptr) return 0;

    // Copy the input data to the C-string and null-terminate it.
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test with the C-string.
    icalproperty *property = icalproperty_new_patchparameter(input);

    // If the property is created, attempt to access some of its properties to increase coverage.
    if (property != nullptr) {
        // Example: Get and manipulate some property attributes
        icalproperty_kind kind = icalproperty_isa(property);
        if (kind != ICAL_NO_PROPERTY) {
            // Perform additional operations to increase code coverage
            const char* prop_name = icalproperty_get_patchparameter(property);
            if (prop_name != nullptr) {
                // Do something with prop_name to ensure it's being processed
                size_t prop_name_len = strlen(prop_name);
                if (prop_name_len > 0) {
                    // Dummy operation to use prop_name
                    volatile char first_char = prop_name[0];
                }
            }
        }
        icalproperty_free(property);
    }

    // Clean up: free the allocated memory.
    free(input);

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

    LLVMFuzzerTestOneInput_1067(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
