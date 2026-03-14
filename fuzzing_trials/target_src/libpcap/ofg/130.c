#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    const char *device = "lo"; // Loopback interface for testing

    // Open a live capture handle
    pcap_handle = pcap_open_live(device, BUFSIZ, 1, 1000, errbuf);
    if (pcap_handle == NULL) {
        return 0; // If unable to open, exit the fuzzer
    }

    // Ensure size is not zero to avoid passing NULL to pcap_inject
    if (size > 0) {
        // Call the function-under-test
        pcap_inject(pcap_handle, data, size);
    }

    // Close the pcap handle
    pcap_close(pcap_handle);

    return 0;
}