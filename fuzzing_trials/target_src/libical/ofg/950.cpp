#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_950(const uint8_t *data, size_t size) {
    // Initialize an icalcomponent from the input data
    icalcomponent *component = NULL;
    
    // Ensure the size is non-zero and data is not NULL
    if (size > 0 && data != NULL) {
        // Create a temporary string to hold the input data
        char *temp_data = (char *)malloc(size + 1);
        if (temp_data == NULL) {
            return 0; // Return if memory allocation fails
        }
        
        // Copy the data into the temporary string and null-terminate it
        memcpy(temp_data, data, size);
        temp_data[size] = '\0';
        
        // Parse the string into an icalcomponent
        component = icalparser_parse_string(temp_data);
        
        // Free the temporary string
        free(temp_data);
    }

    // Call the function-under-test if the component is successfully created
    if (component != NULL) {
        icalproperty *property = icalcomponent_get_current_property(component);
        
        // For fuzzing purposes, we do not need to do anything with the property
        // Just ensure the function is called
        
        // Free the icalcomponent
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

    LLVMFuzzerTestOneInput_950(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
