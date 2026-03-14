#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_75(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int immediate_mode;

    // Ensure the data size is sufficient to extract an integer for immediate_mode
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a pcap_t handle using pcap_open_dead
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Extract an integer from the data to use as the immediate_mode parameter
    immediate_mode = *(int *)data;

    // Call the function-under-test
    pcap_set_immediate_mode(pcap_handle, immediate_mode);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}