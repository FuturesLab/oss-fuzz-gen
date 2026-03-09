#include <stdint.h>
#include <pcap/pcap.h>
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int immediate_mode;

    // Initialize pcap handle with a non-null value
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Ensure there's enough data to extract an integer for immediate_mode
    if (size < sizeof(int)) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Extracting an integer from the data
    immediate_mode = *(const int *)data;

    // Call the function-under-test
    pcap_set_immediate_mode(pcap_handle, immediate_mode);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}