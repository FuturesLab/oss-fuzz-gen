#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <cstring>  // For strlen

extern "C" int LLVMFuzzerTestOneInput_913(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated to avoid buffer overflow
    if (size == 0 || data[size - 1] != '\0') {
        // Create a new buffer with an extra byte for the null terminator
        uint8_t *null_terminated_data = new uint8_t[size + 1];
        memcpy(null_terminated_data, data, size);
        null_terminated_data[size] = '\0';

        // Initialize the necessary structures for the function call
        icalcomponent *component = icalcomponent_new_from_string(reinterpret_cast<const char*>(null_terminated_data));
        delete[] null_terminated_data;  // Clean up the temporary buffer
        
        int year = 2023;  // Use a fixed year for fuzzing
        icalarray *array = icalarray_new(sizeof(icaltimetype), 10);

        // Ensure that component and array are not NULL before calling the function
        if (component != nullptr && array != nullptr) {
            // Call the function-under-test
            icaltimezone_expand_vtimezone(component, year, array);
        }

        // Clean up
        if (component != nullptr) {
            icalcomponent_free(component);
        }
        if (array != nullptr) {
            icalarray_free(array);
        }
    }

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

    LLVMFuzzerTestOneInput_913(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
