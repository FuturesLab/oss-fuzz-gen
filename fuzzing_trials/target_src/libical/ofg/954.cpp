#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_954(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a C string
    if (size == 0) {
        return 0; // Exit early if size is zero
    }

    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_new_patchversion(cstr);

    // Additional logic to ensure code coverage
    if (prop != NULL) {
        // Use the property in some way to increase coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind == ICAL_PATCHVERSION_PROPERTY) {
            // Perform further operations if needed
            const char *value = icalproperty_get_patchversion(prop);
            if (value != NULL) {
                // Process the value to increase coverage
                size_t len = strlen(value);
                if (len > 0) {
                    // Example operation: check the first character
                    char first_char = value[0];
                    if (first_char == 'v') {
                        // Do something specific if the value starts with 'v'
                        // For example, manipulate the property further
                        icalproperty_set_patchversion(prop, "v2.0");
                        const char *new_value = icalproperty_get_patchversion(prop);
                        if (new_value != NULL) {
                            // Further processing to increase coverage
                            size_t new_len = strlen(new_value);
                            if (new_len > 0) {
                                // Another example operation
                                char new_first_char = new_value[0];
                                if (new_first_char == 'v') {
                                    // Do something specific if the new value starts with 'v'
                                }
                            }
                        }
                    }
                }
            }
        }
        icalproperty_free(prop);
    }

    free(cstr);

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

    LLVMFuzzerTestOneInput_954(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
