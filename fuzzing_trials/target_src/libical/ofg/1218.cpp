#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_1218(const uint8_t *data, size_t size) {
    // Initialize a dummy icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure that the data is not NULL and has a reasonable size
    if (data != NULL && size > 0) {
        // Copy the input data to a string with a null terminator
        char *data_str = (char *)malloc(size + 1);
        if (data_str != NULL) {
            memcpy(data_str, data, size);
            data_str[size] = '\0'; // Null terminate the string

            // Try setting a property value from the input data
            icalproperty_set_comment(prop, data_str);

            // Free the allocated string
            free(data_str);
        }
    }

    // Call the function-under-test
    struct icaltimetype maxdate = icalproperty_get_maxdate(prop);

    // Clean up
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

    LLVMFuzzerTestOneInput_1218(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
