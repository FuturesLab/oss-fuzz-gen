#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Correct include path for libical
}

extern "C" int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    // Ensure size is large enough to create a valid string
    if (size < 1) return 0;

    // Create a null-terminated string from the input data
    char *inputData = (char *)malloc(size + 1);
    if (!inputData) return 0;
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create an icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(inputData);
    
    // Free the input data as it's no longer needed
    free(inputData);

    // If component creation failed, exit
    if (!component) return 0;

    // Call the function-under-test
    const char *componentName = icalcomponent_get_component_name(component);

    // Use the componentName for further processing if needed
    // For now, just ensure it's not NULL by checking its value
    if (componentName) {
        // Normally, you might do something with componentName here
    }

    // Clean up by freeing the icalcomponent
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_164(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
