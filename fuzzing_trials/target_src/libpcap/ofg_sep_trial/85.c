#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int datalink_type;

    // Initialize pcap handle with a dummy device
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Ensure the data size is sufficient for an int
    if (size < sizeof(int)) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Extract an int from the input data
    datalink_type = *(const int *)data;

    // Call the function-under-test
    int result = pcap_set_datalink(pcap_handle, datalink_type);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}