#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h> // Include for memcpy
#include <stdio.h>  // Include for printf (optional for debugging)

int LLVMFuzzerTestOneInput_352(const uint8_t *data, size_t size) {
    // Declare and initialize the sleep time variable
    int sleep_time = 0;

    // Ensure the size is sufficient to avoid overflow
    if (size >= sizeof(int)) {
        // Use the first 4 bytes of the input data to create an integer
        memcpy(&sleep_time, data, sizeof(int)); // Use memcpy for safety
        sleep_time &= 0x7FFFFFFF; // Mask to ensure it's non-negative
    } else if (size > 0) {
        // If the input is smaller than an integer, use the available data
        memcpy(&sleep_time, data, size); // Use memcpy for safety
        sleep_time &= 0x7FFFFFFF; // Mask to ensure it's non-negative
    }

    // Ensure that sleep_time is not zero to invoke sqlite3_sleep effectively
    if (sleep_time == 0) {
        sleep_time = 1; // Set a minimum sleep time to ensure the function is called
    }

    // Call the function under test
    sqlite3_sleep(sleep_time);

    return 0;
}