#include <stdint.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract two integers
    if (size < 2 * sizeof(int)) {
        return 0;
    }

    // Extract two integers from the input data
    int linktype = *((int*)data);
    int snaplen = *((int*)(data + sizeof(int)));

    // Call the function-under-test
    pcap_t *pcap_handle = pcap_open_dead(linktype, snaplen);

    // If the handle is not NULL, close it
    if (pcap_handle != NULL) {
        pcap_close(pcap_handle);
    }

    return 0;
}