#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a fake pcap_t handle using pcap_open_dead
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Call the function-under-test with the pcap handle
    int minor_version = pcap_minor_version(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}