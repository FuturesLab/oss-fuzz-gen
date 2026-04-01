#include <pcap.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int snaplen;

    // Initialize pcap handle with a non-null value
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max snaplen

    // Ensure the data size is sufficient to extract an integer
    if (size < sizeof(int)) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Use the first 4 bytes of data as the snaplen value
    snaplen = *(int *)data;

    // Call the function under test
    pcap_set_snaplen(pcap_handle, snaplen);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}