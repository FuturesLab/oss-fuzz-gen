#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_856(const uint8_t *data, size_t size) {
    // Initialize the library
    icalcomponent *component = nullptr;

    // Ensure that the size is non-zero to avoid creating an empty component
    if (size > 0) {
        // Create a temporary string buffer from the input data
        char *tempBuffer = (char *)malloc(size + 1);
        if (tempBuffer == nullptr) {
            return 0; // Exit if memory allocation fails
        }

        memcpy(tempBuffer, data, size);
        tempBuffer[size] = '\0'; // Null-terminate the string

        // Parse the component from the string buffer
        component = icalparser_parse_string(tempBuffer);

        free(tempBuffer); // Free the temporary buffer
    }

    // If a valid component was created, strip errors
    if (component != nullptr) {
        icalcomponent_strip_errors(component);
        icalcomponent_free(component); // Free the component after use
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

    LLVMFuzzerTestOneInput_856(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
