#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include the string.h library for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Convert input data to a null-terminated string
    char *input_str = (char *)malloc(size + 1);
    if (!input_str) {
        return 0; // If memory allocation fails, return immediately
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Initialize an icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(input_str);

    // If the component is successfully created, call the function-under-test
    if (component != NULL) {
        // Call the function-under-test
        struct icaltimetype due_time = icalcomponent_get_due(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the allocated string
    free(input_str);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_132(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
