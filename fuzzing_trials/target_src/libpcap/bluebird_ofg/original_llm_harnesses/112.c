#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Define the fuzzing function
int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for creating a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the device name and ensure it is null-terminated
    char device[size + 1];
    memcpy(device, data, size);
    device[size] = '\0';

    // Call the function-under-test
    char *result = pcap_lookupdev(device);

    // Since pcap_lookupdev returns a pointer to a string or NULL, we don't need to process the result further
    // Any necessary cleanup would be done here if needed

    return 0;
}