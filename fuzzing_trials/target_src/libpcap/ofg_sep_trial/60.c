#include <stdint.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Initialize a pcap_t structure
    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0; // Return if pcap_open_dead fails
    }

    // Call the function-under-test
    int result = pcap_is_swapped(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}