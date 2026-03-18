#include <pcap.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int rfmon;

    // Initialize pcap handle
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Ensure data is not empty and use it to determine the rfmon value
    if (size > 0) {
        rfmon = (int)(data[0] % 2); // Use the first byte to set rfmon to 0 or 1
    } else {
        rfmon = 0; // Default to 0 if size is 0
    }

    // Call the function-under-test
    int result = pcap_set_rfmon(pcap_handle, rfmon);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}