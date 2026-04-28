#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_320(const uint8_t *data, size_t size) {
    // Initialize the icalcomponent from the input data
    icalcomponent *component = nullptr;

    // Ensure the data is not empty to create a valid string
    if (size > 0) {
        // Allocate memory for a null-terminated string
        char *ical_str = (char *)malloc(size + 1);
        if (ical_str == nullptr) {
            return 0; // Memory allocation failed
        }

        // Copy the input data to the string and null-terminate it
        memcpy(ical_str, data, size);
        ical_str[size] = '\0';

        // Parse the string into an icalcomponent
        component = icalparser_parse_string(ical_str);

        // Free the allocated string memory
        free(ical_str);
    }

    // If the component is successfully created, call the function-under-test
    if (component != nullptr) {
        const char *comment = icalcomponent_get_comment(component);
        
        // Use the comment in some way to prevent it from being optimized out
        if (comment != nullptr) {
            // For example, check the length of the comment
            size_t comment_length = strlen(comment);
            (void)comment_length; // Suppress unused variable warning
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

    LLVMFuzzerTestOneInput_320(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
