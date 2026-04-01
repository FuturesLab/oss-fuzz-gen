#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Initialize pcap_t structure using pcap_open_dead
    // pcap_open_dead is used to create a pcap_t structure for testing purposes
    // DLT_RAW is a generic link-layer type, and 65535 is the snapshot length
    pcap_handle = pcap_open_dead(DLT_RAW, 65535);

    if (pcap_handle != NULL) {
        // Call the function-under-test
        int minor_version = pcap_minor_version(pcap_handle);

        // Use the minor_version in some way to avoid compiler optimizations
        if (minor_version < 0) {
            // Handle error case (though this should not happen with pcap_open_dead)
        }

        // Close the pcap handle
        pcap_close(pcap_handle);
    }

    return 0;
}