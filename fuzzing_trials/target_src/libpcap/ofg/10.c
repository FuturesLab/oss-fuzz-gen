#include <stdint.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Open a fake pcap handle for testing
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) return 0;

    // Use the data as a fake packet to test pcap functionality
    struct pcap_pkthdr header;
    header.caplen = size;
    header.len = size;

    // Call the function-under-test
    char *error_message = pcap_geterr(pcap_handle);

    // Use the error_message in some way to avoid compiler optimizations
    if (error_message != NULL) {
        volatile char *volatile_message = error_message;
        (void)volatile_message;
    }

    // Close the pcap handle
    pcap_close(pcap_handle);

    return 0;
}