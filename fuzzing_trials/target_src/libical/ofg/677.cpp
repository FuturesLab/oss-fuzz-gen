#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <libical/ical.h>

extern "C" {
    // Function-under-test
    struct icaldurationtype icalproperty_get_duration(const icalproperty *);
}

extern "C" int LLVMFuzzerTestOneInput_677(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid icalproperty
    if (size < 2) {
        return 0;
    }

    // Convert the input data to a string to use with icaldurationtype_from_string
    char duration_str[2] = {static_cast<char>(data[0]), '\0'};

    // Create a dummy icalproperty for fuzzing
    struct icaldurationtype duration_type = icaldurationtype_from_string(duration_str);
    icalproperty *prop = icalproperty_new_duration(duration_type);

    // Call the function-under-test
    struct icaldurationtype duration = icalproperty_get_duration(prop);

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

    LLVMFuzzerTestOneInput_677(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
