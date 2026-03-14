#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Initialize pcap_t
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max packet size

    if (handle == NULL) {
        return 0;
    }

    // Ensure size is non-zero for valid data access
    if (size < sizeof(int)) {
        pcap_close(handle);
        return 0;
    }

    // Extract an integer from the data for the datalink type
    int datalink_type = *((int *)data);

    // Call the function-under-test
    int result = pcap_set_datalink(handle, datalink_type);

    // Clean up
    pcap_close(handle);

    return 0;
}