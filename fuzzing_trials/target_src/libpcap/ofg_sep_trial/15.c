#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Initialize pcap_t using pcap_open_dead as a placeholder
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    int selectable_fd = pcap_get_selectable_fd(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}