#include <stdint.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int promisc_mode;

    // Ensure the data size is sufficient to extract the promisc_mode
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize the pcap handle with a non-NULL value
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Extract the promisc_mode from the input data
    promisc_mode = *((int *)data);

    // Call the function under test
    int result = pcap_set_promisc(pcap_handle, promisc_mode);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}