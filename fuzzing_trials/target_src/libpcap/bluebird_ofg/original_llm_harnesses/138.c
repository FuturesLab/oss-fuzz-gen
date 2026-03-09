#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535); // Open a fake pcap handle
    int snaplen = 0;

    // Ensure size is large enough to extract an integer for snaplen
    if (size >= sizeof(int)) {
        snaplen = *(const int*)data; // Extract snaplen from data
    }

    // Call the function-under-test
    int result = pcap_set_snaplen(pcap_handle, snaplen);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}