#include <stdint.h>
#include <stdlib.h>
#include <libical/ical.h>

extern "C" {
    #include <string.h> // Include the string.h library for memcpy
}

extern "C" int LLVMFuzzerTestOneInput_762(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    icalcomponent *component = nullptr;
    
    if (size > 0) {
        // Convert input data to a string
        char *input_data = (char *)malloc(size + 1);
        if (input_data == nullptr) {
            return 0; // Exit if memory allocation fails
        }
        memcpy(input_data, data, size);
        input_data[size] = '\0';
        
        // Parse the string into an icalcomponent
        component = icalparser_parse_string(input_data);
        
        // Free the input data as it is no longer needed
        free(input_data);
    }

    if (component != nullptr) {
        // Call the function-under-test
        int error_count = icalcomponent_count_errors(component);

        // Clean up the icalcomponent
        icalcomponent_free(component);
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

    LLVMFuzzerTestOneInput_762(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
