#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_375(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Copy the data to a new buffer and null-terminate it
    char *summary = (char *)malloc(size + 1);
    if (summary == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(summary, data, size);
    summary[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_summary(component, summary);

    // Additional operations to increase code coverage
    const char *retrieved_summary = icalcomponent_get_summary(component);
    if (retrieved_summary != NULL) {
        // Perform some checks or operations to ensure the summary was set correctly
        if (strcmp(retrieved_summary, summary) == 0) {
            // Summary was set and retrieved correctly
        }
    }

    // Clean up
    free(summary);
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_375(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
