#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1036(const uint8_t *data, size_t size) {
    // Initialize a string with the input data
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0;
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Create a new icalcomponent from the input string
    icalcomponent *comp = icalparser_parse_string(input);
    if (comp != NULL) {
        // Call the function-under-test
        const char *location = icalcomponent_get_location(comp);

        // Use the returned location string in some way
        if (location != NULL) {
            // For demonstration, we just print it out
            // In a real fuzzing scenario, we might analyze it or check for certain properties
            printf("Location: %s\n", location);
        }

        // Free the icalcomponent
        icalcomponent_free(comp);
    }

    // Free the allocated input string
    free(input);

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

    LLVMFuzzerTestOneInput_1036(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
