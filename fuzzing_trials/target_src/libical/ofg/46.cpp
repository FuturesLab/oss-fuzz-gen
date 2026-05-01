#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/icalcomponent.h>
    #include <libical/icalproperty.h>
}

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Check if the input data size is sufficient
    if (size < 1) {
        return 0;
    }

    // Initialize variables
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (!component) {
        return 0; // Failed to create component
    }

    // Map the first byte of data to a status value
    icalproperty_status status;
    switch (data[0] % 3) {
        case 0:
            status = ICAL_STATUS_TENTATIVE;
            break;
        case 1:
            status = ICAL_STATUS_CONFIRMED;
            break;
        case 2:
            status = ICAL_STATUS_CANCELLED;
            break;
        default:
            status = ICAL_STATUS_NONE;
            break;
    }

    // Set the status of the component
    icalcomponent_set_status(component, status);

    // Optionally, add more properties or manipulate the component further
    // based on the input data to increase code coverage.

    // Clean up
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_46(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
