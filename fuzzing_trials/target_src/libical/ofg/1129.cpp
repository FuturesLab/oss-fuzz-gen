#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy
#include <libical/ical.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1129(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the string and ensure it's null-terminated
    char *ical_str = (char *)malloc(size + 1);
    if (ical_str == NULL) {
        return 0;
    }
    memcpy(ical_str, data, size);
    ical_str[size] = '\0';

    // Parse the string into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_str);

    // Ensure the component is not NULL before passing it to the function
    if (component != NULL) {
        // Call the function-under-test
        icalcomponent_convert_errors(component);

        // Clean up the component
        icalcomponent_free(component);
    }

    // Free the allocated string
    free(ical_str);

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

    LLVMFuzzerTestOneInput_1129(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
