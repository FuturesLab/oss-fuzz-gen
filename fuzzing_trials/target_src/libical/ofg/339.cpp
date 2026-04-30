#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_339(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for a null-terminated string
    if (size == 0) {
        return 0;
    }
    
    // Create a null-terminated string from the input data
    char *restriction = (char *)malloc(size + 1);
    if (!restriction) {
        return 0;
    }
    memcpy(restriction, data, size);
    restriction[size] = '\0';

    // Create an icalproperty object with a specific property type to ensure proper coverage
    icalproperty *prop = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (prop == NULL) {
        free(restriction);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_summary(prop, restriction);

    // Additional calls to increase code coverage
    const char *summary = icalproperty_get_summary(prop);
    if (summary) {
        // Do something with the summary to ensure it is processed
        size_t summary_length = strlen(summary);
        if (summary_length > 0) {
            // Example of further processing
            char *copied_summary = (char *)malloc(summary_length + 1);
            if (copied_summary) {
                strcpy(copied_summary, summary);
                free(copied_summary);
            }
        }
    }

    // Attempt to parse the summary as an icalcomponent to increase coverage
    icalcomponent *comp = icalparser_parse_string(restriction);
    if (comp) {
        // Process the component to ensure it's utilized
        icalcomponent_free(comp);
    }

    // Clean up
    icalproperty_free(prop);
    free(restriction);

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

    LLVMFuzzerTestOneInput_339(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
