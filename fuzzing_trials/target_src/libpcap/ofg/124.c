#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Initialize a pcap_t handle using pcap_create with a non-NULL device name
    pcap_handle = pcap_create("any", errbuf);
    if (pcap_handle == NULL) {
        return 0; // Failed to create pcap handle, exit early
    }

    // Ensure the size is at least 1 to access data[0]
    if (size < 1) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Use the first byte of data to set the promisc parameter
    int promisc = data[0] % 2; // Ensure promisc is either 0 or 1

    // Call the function under test
    int result = pcap_set_promisc(pcap_handle, promisc);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}