#include <stddef.h>
#include <stdint.h>
#include <pcap.h>
#include <string.h>

// Function to be used by the fuzzer
int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the device name and ensure it's null-terminated
    char dev_name[256];
    size_t copy_size = size < sizeof(dev_name) - 1 ? size : sizeof(dev_name) - 1;
    memcpy(dev_name, data, copy_size);
    dev_name[copy_size] = '\0';

    // Call the function-under-test
    char errbuf[PCAP_ERRBUF_SIZE];
    char *result = pcap_lookupdev(errbuf);

    // Normally, you would check the result and handle errors, but for fuzzing,
    // we are primarily interested in discovering memory corruption issues.

    return 0;
}