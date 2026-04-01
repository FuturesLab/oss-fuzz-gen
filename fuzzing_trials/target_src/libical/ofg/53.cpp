#include <stdint.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    icalcomponent_kind kind = *(reinterpret_cast<const icalcomponent_kind*>(data));

    // Call the function-under-test
    icalcomponent *component = icalcomponent_new(kind);

    // Clean up the created component to avoid memory leaks
    if (component != NULL) {
        icalcomponent_free(component);
    }

    return 0;
}