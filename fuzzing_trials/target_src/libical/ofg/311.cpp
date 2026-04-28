#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include the necessary header for memcpy
#include <libical/ical.h> // Include the necessary header for icalcomponent

extern "C" {
    #include <libical/ical.h> // Ensure libical headers are within extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_311(const uint8_t *data, size_t size) {
    // Initialize a new icalcomponent from the input data
    // Ensure the data is null-terminated
    char *inputData = (char *)malloc(size + 1);
    if (inputData == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create an icalcomponent from the string
    icalcomponent *component = icalparser_parse_string(inputData);
    free(inputData);

    if (component != NULL) {
        // Call the function-under-test
        char *icalString = icalcomponent_as_ical_string(component);

        // Free the returned string if not NULL
        if (icalString != NULL) {
            free(icalString);
        }

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

    LLVMFuzzerTestOneInput_311(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
