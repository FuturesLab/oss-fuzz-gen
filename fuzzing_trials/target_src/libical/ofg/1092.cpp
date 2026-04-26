#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1092(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a string
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        return 0;
    }
    memcpy(str, data, size);
    str[size] = '\0';

    // Create an icalproperty from the input data
    icalproperty *prop = icalproperty_new_from_string(str);

    // Create an icalvalue from the input data
    // Since icalvalue_new_from_string requires icalvalue_kind, we need to provide it
    // For demonstration, let's assume we use ICAL_STRING_VALUE as the kind
    icalvalue *value = icalvalue_new_from_string(ICAL_STRING_VALUE, str);

    // Ensure neither prop nor value is NULL before calling the function
    if (prop != NULL && value != NULL) {
        // Call the function-under-test
        icalproperty_set_value(prop, value);
    }

    // Clean up
    if (prop != NULL) {
        icalproperty_free(prop);
    }
    if (value != NULL) {
        icalvalue_free(value);
    }
    free(str);

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

    LLVMFuzzerTestOneInput_1092(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
