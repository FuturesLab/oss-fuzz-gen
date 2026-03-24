#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a meaningful test
    if (size < sizeof(void*)) {
        return 0;
    }

    // Use the data as a pointer to pass to the function
    const void *ptr = static_cast<const void*>(data);

    // Call the function-under-test
    bool result = icalcomponent_isa_component(ptr);

    // Optionally, use the result to influence further behavior
    // (though for fuzzing we typically just want to ensure no crashes)
    if (result) {
        // Do something if the result is true, if needed
    }

    return 0;
}