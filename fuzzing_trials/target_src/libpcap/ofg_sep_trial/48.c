#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure the size is not zero to avoid empty input
    if (size == 0) {
        return 0;
    }

    // Open a fake pcap handle using a memory buffer
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Call the function under test
    int datalink_type = pcap_datalink(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}