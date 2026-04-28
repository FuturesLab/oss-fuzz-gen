#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_939(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Use the data to create a string, assuming it is null-terminated
    char *ical_string = (char *)malloc(size + 1);
    if (ical_string == nullptr) {
        return 0;
    }
    
    memcpy(ical_string, data, size);
    ical_string[size] = '\0';

    // Parse the iCal string
    icalcomponent *comp = icalparser_parse_string(ical_string);

    // Clean up
    if (comp != nullptr) {
        icalcomponent_free(comp);
    }
    free(ical_string);

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

    LLVMFuzzerTestOneInput_939(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
