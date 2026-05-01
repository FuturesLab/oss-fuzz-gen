#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary string buffer from the input data
    char *str = (char *)malloc(size + 1);
    if (str == NULL) {
        return 0;
    }
    memcpy(str, data, size);
    str[size] = '\0';  // Null-terminate the string

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(str);
    if (component != NULL) {
        // Call the function-under-test
        const char *location = icalcomponent_get_location(component);

        // Use the location in some way to avoid compiler optimizations removing the call
        if (location != NULL) {
            // Print the location (for debugging purposes)
            // printf("Location: %s\n", location);
        }

        // Free the icalcomponent
        icalcomponent_free(component);
    }

    // Free the temporary string buffer
    free(str);

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

    LLVMFuzzerTestOneInput_140(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
