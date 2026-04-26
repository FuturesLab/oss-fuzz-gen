#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Create a new icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);

    // Ensure that the property is not NULL
    if (prop == NULL) {
        return 0;
    }

    // Use the provided data to set a property value
    if (size > 0) {
        char *value = (char *)malloc(size + 1);
        if (value != NULL) {
            memcpy(value, data, size);
            value[size] = '\0'; // Null-terminate the string
            icalproperty_set_comment(prop, value);
            free(value);
        }
    }

    // Call the function-under-test
    int max_results = icalproperty_get_maxresults(prop);

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

    LLVMFuzzerTestOneInput_39(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
