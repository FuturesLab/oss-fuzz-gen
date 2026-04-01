#include <cstdint>
#include <cstdlib>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid input.
    if (size < sizeof(void *)) {
        return 0;
    }

    // Cast the input data to a void pointer.
    const void *input = static_cast<const void *>(data);

    // Call the function-under-test.
    bool result = icalcomponent_isa_component(input);

    // Use the result to prevent compiler optimizations.
    volatile bool prevent_optimization = result;
    (void)prevent_optimization;

    return 0;
}