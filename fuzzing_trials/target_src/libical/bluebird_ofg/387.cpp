#include <sys/stat.h>
#include "libical/ical.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_387(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to prevent buffer overflow
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Initialize the icalcomponent from the input data
    icalcomponent *component = icalcomponent_new_from_string(inputData);
    
    if (component != NULL) {
        // Call the function-under-test
        const char *x_name = icalcomponent_get_x_name(component);

        // Optionally print the result for debugging purposes
        if (x_name != NULL) {
            printf("X-Name: %s\n", x_name);
        }

        // Free the component
        icalcomponent_free(component);
    }

    // Free the allocated input data
    free(inputData);

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

    LLVMFuzzerTestOneInput_387(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
