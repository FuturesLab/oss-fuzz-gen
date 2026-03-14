#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a fake pcap_t object using pcap_open_dead
    pcap_handle = pcap_open_dead(DLT_RAW, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    int minor_version = pcap_minor_version(pcap_handle);

    // Cleanup
    pcap_close(pcap_handle);

    return 0;
}