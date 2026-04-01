#include <stdint.h>
#include <pcap.h>

extern int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_direction_t direction;

    // Initialize pcap_handle with a non-NULL value
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0; // If pcap_open_dead fails, exit early
    }

    // Use the data to determine the direction, ensuring it's a valid pcap_direction_t
    if (size > 0) {
        direction = (pcap_direction_t)(data[0] % 3); // 0, 1, or 2
    } else {
        direction = PCAP_D_INOUT; // Default direction if no data
    }

    // Call the function-under-test
    int result = pcap_setdirection(pcap_handle, direction);

    // Cleanup
    pcap_close(pcap_handle);

    return 0;
}