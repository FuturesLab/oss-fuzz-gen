#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Open a dead pcap handle for testing
    pcap_handle = pcap_open_dead(DLT_RAW, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Ensure we have enough data to extract an integer
    if (size < sizeof(int)) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Use the first 4 bytes of data as the timestamp type
    int tstamp_type = *((const int *)data);

    // Call the function under test
    pcap_set_tstamp_type(pcap_handle, tstamp_type);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}