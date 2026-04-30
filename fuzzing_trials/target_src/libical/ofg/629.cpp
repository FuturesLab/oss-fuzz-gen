#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // For malloc and free
#include <string.h> // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_629(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to work with
    if (size < 1) {
        return 0;
    }

    // Create a dummy icalvalue object from the input data
    // For simplicity, we will assume that the input data is a valid string representation of an icalvalue
    char *icalvalue_str = (char *)malloc(size + 1);
    if (icalvalue_str == NULL) {
        return 0;
    }
    memcpy(icalvalue_str, data, size);
    icalvalue_str[size] = '\0';

    // Parse the string into an icalvalue
    // We need to provide a valid icalvalue_kind. For fuzzing, we can try a common kind like ICAL_STRING_VALUE
    icalvalue *value = icalvalue_new_from_string(ICAL_STRING_VALUE, icalvalue_str);
    free(icalvalue_str);

    // Check if the value was created successfully
    if (value == NULL) {
        return 0;
    }

    // Call the function-under-test
    icalvalue_kind kind = icalvalue_isa(value);

    // Clean up
    icalvalue_free(value);

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

    LLVMFuzzerTestOneInput_629(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
