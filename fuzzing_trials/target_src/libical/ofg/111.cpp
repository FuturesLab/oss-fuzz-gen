#include <cstddef>  // For size_t
#include <cstdint>  // For uint8_t
#include <cstdlib>  // For malloc, free
#include <cstring>  // For memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Convert the input data to a string, ensuring it's null-terminated
    char *inputStr = (char *)malloc(size + 1);
    if (inputStr == NULL) return 0; // If allocation fails, return early
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Parse the input data as an iCalendar component
    icalcomponent *component = icalparser_parse_string(inputStr);

    if (component != NULL) {
        // Convert the component back to a string
        char *str = icalcomponent_as_ical_string(component);
        if (str != NULL) {
            // Normally you might print or log the string, but we'll just free it here
            icalmemory_free_buffer(str);
        }

        // Free the component after use
        icalcomponent_free(component);
    }

    // Free the allocated input string
    free(inputStr);

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

    LLVMFuzzerTestOneInput_111(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
