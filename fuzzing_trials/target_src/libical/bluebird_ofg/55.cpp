#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "libical/ical.h"

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create an icalpropiter object
    if (size < sizeof(icalpropiter)) {
        return 0;
    }

    // Create an icalpropiter object from the input data
    icalpropiter iter;
    memcpy(&iter, data, sizeof(icalpropiter));

    // Call the function-under-test
    bool isValid = icalpropiter_is_valid(&iter);

    // Use the result to prevent the compiler from optimizing it away
    if (isValid) {
        // Do something if valid, e.g., print or log (omitted here for simplicity)
    }

    return 0;
}