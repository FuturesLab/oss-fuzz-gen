#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput_1360(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for safety
    char *ical_data = (char *)malloc(size + 1);
    if (ical_data == NULL) {
        return 0;
    }
    memcpy(ical_data, data, size);
    ical_data[size] = '\0';

    // Parse the input data into an icalcomponent
    icalcomponent *component = icalparser_parse_string(ical_data);
    if (component != NULL) {
        // Call the function-under-test
        const char *summary = icalcomponent_get_summary(component);
        
        // For debugging purposes, you can print the summary
        if (summary != NULL) {
            printf("Summary: %s\n", summary);
        }

        // Clean up the icalcomponent
        icalcomponent_free(component);
    }

    // Free the allocated memory
    free(ical_data);

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

    LLVMFuzzerTestOneInput_1360(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
