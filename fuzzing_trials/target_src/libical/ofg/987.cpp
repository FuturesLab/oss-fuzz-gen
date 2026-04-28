#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_987(const uint8_t *data, size_t size) {
    // Initialize libical
    icalcomponent *comp = nullptr;
    icaltimetype due_time;

    // Create a temporary string buffer to hold the input data
    char *buffer = (char *)malloc(size + 1);
    if (buffer == nullptr) {
        return 0;
    }

    // Copy the input data to the buffer and null-terminate it
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the input data as an iCalendar component
    comp = icalparser_parse_string(buffer);

    // If parsing was successful, call the function-under-test
    if (comp != nullptr) {
        due_time = icalcomponent_get_due(comp);

        // Clean up the component
        icalcomponent_free(comp);
    }

    // Free the buffer
    free(buffer);

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

    LLVMFuzzerTestOneInput_987(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
