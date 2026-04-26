#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1367(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated to prevent buffer overflow
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0'; // Null-terminate the input data

    // Initialize libical memory management
    icalmemory_add_tmp_buffer(null_terminated_data);

    // Create an icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(null_terminated_data);
    if (component == NULL) {
        // If the input data cannot be parsed into a valid icalcomponent, exit
        free(null_terminated_data);
        return 0;
    }

    // Initialize an icalcompiter for the component
    icalcomponent *iter_component = icalcomponent_get_first_component(component, ICAL_ANY_COMPONENT);
    if (iter_component != NULL) {
        // Initialize the iterator
        icalcompiter iter = icalcomponent_begin_component(component, ICAL_ANY_COMPONENT);

        // Call the function-under-test
        icalcomponent *prior_component = icalcompiter_prior(&iter);
    }

    // Cleanup
    icalcomponent_free(component);
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

    LLVMFuzzerTestOneInput_1367(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
