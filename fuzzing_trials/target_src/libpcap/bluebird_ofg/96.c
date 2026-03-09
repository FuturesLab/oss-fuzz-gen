#include <stdint.h>
#include <stddef.h>
#include "pcap/pcap.h"  // Include the pcap library header

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to form an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first few bytes of data as an integer
    int status_code = *(const int *)data;

    // Call the function-under-test
    const char *result = pcap_statustostr(status_code);

    // Use the result to avoid any compiler optimizations that might skip the call
    if (result != NULL) {
        // Do something trivial with the result, like checking its length
        size_t length = 0;
        while (result[length] != '\0') {
            length++;
        }
    }

    return 0;
}