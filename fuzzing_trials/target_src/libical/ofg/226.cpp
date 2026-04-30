#include <cstdint>  // For uint8_t
#include <cstddef>  // For size_t
#include <cstring>  // For strlen

extern "C" {
#include <libical/ical.h>
#include <libical/icalarray.h>
#include <libical/icalcomponent.h>
#include <libical/icaltimezone.h>
}

extern "C" int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated
    char *data_copy = (char *)malloc(size + 1);
    if (data_copy == NULL) {
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0';

    // Initialize variables required for the function call
    icalarray *array = icalarray_new(sizeof(icaltimezone*), 10);
    if (array == NULL) {
        free(data_copy);
        return 0;
    }

    icalcomponent *vtimezone = icalcomponent_new_from_string(data_copy);

    // Ensure that vtimezone is not NULL
    if (vtimezone == NULL) {
        icalarray_free(array);
        free(data_copy);
        return 0;
    }

    // Call the function under test
    icaltimezone_array_append_from_vtimezone(array, vtimezone);

    // Clean up
    icalarray_free(array);
    icalcomponent_free(vtimezone);
    free(data_copy);

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

    LLVMFuzzerTestOneInput_226(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
