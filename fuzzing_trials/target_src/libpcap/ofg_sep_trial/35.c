#include <stdint.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
    pcap_t *p = pcap_open_dead(DLT_EN10MB, 65535); // Create a non-NULL pcap_t pointer
    int protocol = 0; // Initialize protocol to a valid integer value

    if (size > 0) {
        protocol = data[0]; // Use the first byte of data as the protocol value
    }

    // Call the function-under-test
    int result = pcap_set_protocol_linux(p, protocol);

    // Clean up
    pcap_close(p);

    return 0;
}