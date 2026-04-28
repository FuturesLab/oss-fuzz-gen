#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for strlen

extern "C" int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated
    char *null_terminated_data = static_cast<char*>(malloc(size + 1));
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize the icalarray and icalcomponent
    icalarray *array = icalarray_new(sizeof(void*), 10);
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);

    // Ensure component is not NULL
    if (component == NULL) {
        icalarray_free(array);
        free(null_terminated_data);
        return 0;
    }

    // Call the function-under-test
    icaltimezone_array_append_from_vtimezone(array, component);

    // Clean up
    icalcomponent_free(component);
    icalarray_free(array);
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

    LLVMFuzzerTestOneInput_225(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
