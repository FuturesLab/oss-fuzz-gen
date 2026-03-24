#include <cstdint>
#include <cstdlib>
#include <iostream>

// Include necessary headers for the function-under-test
extern "C" {
    #include <libical/ical.h>
}

// Define the fuzzing function
extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an icalcomponent_kind value
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Extract an icalcomponent_kind value from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0]);

    // Call the function-under-test
    const char *result = icalcomponent_kind_to_string(kind);

    // Output the result for debugging purposes
    if (result != nullptr) {
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}