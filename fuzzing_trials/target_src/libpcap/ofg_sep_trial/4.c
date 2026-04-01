#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a pcap_t handle with a valid snapshot length and link-layer type
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and standard snapshot length
    if (pcap_handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    int result = pcap_activate(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}