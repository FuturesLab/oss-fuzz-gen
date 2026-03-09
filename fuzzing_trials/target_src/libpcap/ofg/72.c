#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int buffer_size;

    // Ensure data is large enough to extract an int for buffer_size
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a dummy pcap handle
    pcap_handle = pcap_open_dead(DLT_RAW, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Extract an int from the data for buffer_size
    buffer_size = *((int*)data);

    // Call the function under test
    pcap_set_buffer_size(pcap_handle, buffer_size);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}