#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

// Function prototype for LLVMFuzzerTestOneInput
int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Initialize variables
    pcap_t *p = pcap_open_dead(DLT_EN10MB, 65535); // Open a fake pcap_t structure
    int protocol;

    // Ensure we have enough data to extract an integer for the protocol
    if (size < sizeof(int)) {
        pcap_close(p);
        return 0;
    }

    // Copy the first sizeof(int) bytes from data to protocol
    protocol = *((int *)data);

    // Call the function-under-test
    int result = pcap_set_protocol_linux(p, protocol);

    // Clean up
    pcap_close(p);

    return 0;
}