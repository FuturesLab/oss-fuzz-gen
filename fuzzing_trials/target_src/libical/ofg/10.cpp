#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <cstring> // Include the C++ header for strlen

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an icalcomponent_kind value
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Extract an icalcomponent_kind value from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(*data);

    // Call the function-under-test
    const char *result = icalcomponent_kind_to_string(kind);

    // Use the result to avoid compiler optimizations
    if (result != nullptr) {
        volatile size_t result_length = std::strlen(result); // Use std::strlen from <cstring>
        (void)result_length;
    }

    return 0;
}