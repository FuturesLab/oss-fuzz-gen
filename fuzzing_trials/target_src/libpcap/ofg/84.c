#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int datalink_type;

    // Initialize a pcap handle with a non-NULL value
    handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (handle == NULL) {
        return 0;
    }

    // Ensure data is not empty and size is sufficient for an int
    if (size < sizeof(int)) {
        pcap_close(handle);
        return 0;
    }

    // Use the first 4 bytes of data as the datalink type
    datalink_type = *((int *)data);

    // Call the function-under-test
    pcap_set_datalink(handle, datalink_type);

    // Clean up
    pcap_close(handle);

    return 0;
}