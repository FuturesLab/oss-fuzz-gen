#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Use the data as a pcap file in memory
    pcap_handle = pcap_open_offline_with_tstamp_precision((const char *)data, PCAP_TSTAMP_PRECISION_MICRO, errbuf);

    if (pcap_handle == NULL) {
        return 0;
    }

    // Call the function-under-test
    char *error_message = pcap_geterr(pcap_handle);

    // Use the error message in some way to prevent compiler optimization
    if (error_message != NULL) {
        // Print the error message (or handle it in a way that makes sense for fuzzing)
        (void)error_message; // Suppress unused variable warning
    }

    // Close the pcap handle
    pcap_close(pcap_handle);

    return 0;
}