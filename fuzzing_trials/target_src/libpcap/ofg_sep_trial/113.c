#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    // Allocate memory for the device name buffer
    char device[256];
    
    // Ensure the buffer is null-terminated
    memset(device, 0, sizeof(device));

    // Copy the input data into the device buffer, ensuring it is null-terminated
    size_t copy_size = size < sizeof(device) - 1 ? size : sizeof(device) - 1;
    memcpy(device, data, copy_size);

    // Call the function-under-test
    char *result = pcap_lookupdev(device);

    // Use the result to avoid any compiler optimizations that might skip the call
    if (result != NULL) {
        // Do something with the result, like printing or logging
        // But for fuzzing purposes, we generally do not need to do anything
    }

    return 0;
}