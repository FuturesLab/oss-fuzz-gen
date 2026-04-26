#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>
#include <ctype.h>  // Include ctype.h for the toupper function

extern "C" {
    // Ensure all libical related code is wrapped in extern "C"
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_351(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a non-null string
    if (size < 1) return 0;

    // Allocate memory for the string and ensure it's null-terminated
    char *refid = (char *)malloc(size + 1);
    if (!refid) return 0; // Check for allocation failure
    memcpy(refid, data, size);
    refid[size] = '\0';

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_refid(refid, NULL);

    // Check the result and perform additional operations to increase coverage
    if (prop != NULL) {
        // Access some properties to increase coverage
        icalproperty_kind kind = icalproperty_isa(prop);
        if (kind == ICAL_REFID_PROPERTY) {
            const char *value = icalproperty_get_refid(prop);
            if (value) {
                // Perform some operations with the value to simulate realistic usage
                size_t value_len = strlen(value);
                if (value_len > 0) {
                    // Further manipulate or use the value to increase code paths
                    char *copied_value = (char *)malloc(value_len + 1);
                    if (copied_value) {
                        strcpy(copied_value, value);

                        // Simulate additional processing
                        // Example: Check if the copied value is a valid UUID
                        if (value_len == 36 && value[8] == '-' && value[13] == '-' && value[18] == '-' && value[23] == '-') {
                            // Simulate some processing for valid UUIDs
                            // For example, converting to uppercase
                            for (size_t i = 0; i < value_len; ++i) {
                                copied_value[i] = toupper(copied_value[i]);
                            }
                        }

                        free(copied_value);
                    }
                }
            }
        }
        icalproperty_free(prop);
    }
    free(refid);

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

    LLVMFuzzerTestOneInput_351(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
