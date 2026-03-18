#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a dummy pcap_t handle using pcap_open_dead
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);

    // Ensure pcap_handle is not NULL
    if (pcap_handle == NULL) {
        return 0;
    }

    // Choose a pcap_direction_t value based on the input data
    pcap_direction_t direction;
    if (size > 0) {
        direction = (pcap_direction_t)(data[0] % 3); // 0, 1, or 2
    } else {
        direction = PCAP_D_INOUT; // Default value
    }

    // Call the function-under-test
    int result = pcap_setdirection(pcap_handle, direction);

    // Close the pcap handle
    pcap_close(pcap_handle);

    return 0;
}