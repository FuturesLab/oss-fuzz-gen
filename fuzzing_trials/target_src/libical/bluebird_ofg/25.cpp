#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Initialize libical
    icalcomponent *component = nullptr;

    // Create a temporary string from the input data
    char *temp_data = (char *)malloc(size + 1);
    if (temp_data == nullptr) {
        return 0; // Memory allocation failed
    }
    memcpy(temp_data, data, size);
    temp_data[size] = '\0'; // Null-terminate the string

    // Parse the input data as an iCalendar component
    component = icalparser_parse_string(temp_data);
    if (component != nullptr) {
        // Call the function-under-test
        struct icaltimetype due_time = icalcomponent_get_due(component);

        // Optionally, you can do something with due_time here
        // For example, print or log the due time (not required for fuzzing)

        // Free the component
        icalcomponent_free(component);
    }

    // Free the temporary data
    free(temp_data);

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

    LLVMFuzzerTestOneInput_25(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
