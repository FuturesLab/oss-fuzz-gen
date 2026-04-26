#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a meaningful string
    if (size < 1) {
        return 0;
    }

    // Create an icalcomponent object
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);

    // Create a null-terminated string from the input data
    char *relcalid = (char *)malloc(size + 1);
    if (!relcalid) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(relcalid, data, size);
    relcalid[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_relcalid(component, relcalid);

    // Additional operations to increase code coverage
    // Retrieve the relcalid to ensure the set operation was successful
    const char *retrieved_relcalid = icalcomponent_get_relcalid(component);
    if (retrieved_relcalid) {
        // Use the retrieved_relcalid in some way to ensure it's not optimized out
        size_t retrieved_length = strlen(retrieved_relcalid);
        if (retrieved_length > 0) {
            // Perform some operation with the retrieved_relcalid
            // For example, checking if it matches the original input
            if (strcmp(relcalid, retrieved_relcalid) == 0) {
                // Further operations can be added here
            }
        }
    }

    // Clean up
    free(relcalid);
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

    LLVMFuzzerTestOneInput_26(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
