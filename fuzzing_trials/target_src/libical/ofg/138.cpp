#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary buffer to hold the input data as a string
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }

    // Copy the input data and null-terminate it
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(input_data);

    // If parsing was successful, call the function-under-test
    if (component != NULL) {
        icalcomponent *real_component = icalcomponent_get_first_real_component(component);

        // Perform any additional operations on real_component if needed

        // Free the parsed component
        icalcomponent_free(component);
    }

    // Free the temporary buffer
    free(input_data);

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

    LLVMFuzzerTestOneInput_138(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
