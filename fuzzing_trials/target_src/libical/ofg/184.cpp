#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_184(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create valid inputs
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0;
    }

    // Initialize the icalcomponent
    icalcomponent *comp = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (comp == NULL) {
        return 0;
    }

    // Create two icaltimetype structures from the input data
    struct icaltimetype tt1, tt2;

    // Copy data into the first icaltimetype structure
    memcpy(&tt1, data, sizeof(struct icaltimetype));

    // Copy data into the second icaltimetype structure
    memcpy(&tt2, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Call the function-under-test
    bool result = icalproperty_recurrence_is_excluded(comp, &tt1, &tt2);

    // Clean up
    icalcomponent_free(comp);

    return 0;
}