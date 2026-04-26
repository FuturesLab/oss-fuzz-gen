#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Including necessary headers for icalcomponent and icalparser
extern "C" {
    #include "libical/icalcomponent.h"
    #include "libical/icalmemory.h"  // For icalmemory_free_buffer
    #include "libical/icalparser.h"  // For icalparser_parse_string
}

// Fuzzing target function
extern "C" int LLVMFuzzerTestOneInput_336(const uint8_t *data, size_t size) {
    // Create an icalcomponent from the input data
    char *data_copy = (char *)malloc(size + 1);
    if (data_copy == NULL) {
        return 0;
    }
    memcpy(data_copy, data, size);
    data_copy[size] = '\0'; // Null-terminate to ensure valid string

    // Parse the data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(data_copy);

    // If parsing was successful, test the function under test
    if (component != NULL) {
        char *component_name = icalcomponent_get_component_name_r(component);

        // Free any allocated memory
        if (component_name != NULL) {
            icalmemory_free_buffer(component_name);
        }

        icalcomponent_free(component);
    }

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

    LLVMFuzzerTestOneInput_336(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
