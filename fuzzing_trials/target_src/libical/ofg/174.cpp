#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C-style string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Check if the input size is reasonable for the function under test
    if (size > 0) {
        // Call the function-under-test
        icalproperty *prop = icalproperty_new_xlicmimeencoding(null_terminated_data);

        // Additional operations to ensure code coverage
        if (prop != NULL) {
            // Access some properties or perform operations to ensure the object is used
            icalproperty_kind kind = icalproperty_isa(prop);
            if (kind != ICAL_NO_PROPERTY) {
                // Example: convert to string and back to ensure usage
                const char *prop_str = icalproperty_as_ical_string(prop);
                if (prop_str != NULL) {
                    icalproperty *prop_copy = icalproperty_new_from_string(prop_str);
                    if (prop_copy != NULL) {
                        icalproperty_free(prop_copy);
                    }
                    // No need to free prop_str as it is managed by libical
                }
            }
            icalproperty_free(prop);
        }
    }

    free(null_terminated_data);

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

    LLVMFuzzerTestOneInput_174(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
