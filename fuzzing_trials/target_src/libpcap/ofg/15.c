#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    pcap_t *pcap;

    // Initialize a pcap_t structure with dummy data
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max snapshot length

    if (pcap == NULL) {
        return 0;
    }

    // Call the function-under-test
    int fd = pcap_get_selectable_fd(pcap);

    // Clean up
    pcap_close(pcap);

    return 0;
}