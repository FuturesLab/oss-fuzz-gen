#include <stdint.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int immediate_mode;

    // Initialize a pcap handle
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max snaplen
    if (pcap_handle == NULL) {
        return 0;
    }

    // Ensure the immediate_mode is within a reasonable range
    if (size > 0) {
        immediate_mode = data[0] % 2; // immediate_mode should be 0 or 1
    } else {
        immediate_mode = 1; // Default to 1 if no data is provided
    }

    // Call the function-under-test
    int result = pcap_set_immediate_mode(pcap_handle, immediate_mode);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}