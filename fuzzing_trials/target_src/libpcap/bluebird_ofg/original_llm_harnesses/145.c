#include <stdint.h>
#include <stdlib.h>
#include <pcap/pcap.h>

int LLVMFuzzerTestOneInput_145(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a fake pcap_t structure using pcap_open_dead which doesn't require a real file
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Process the input data with pcap_inject or similar function to utilize the input
    // Note: pcap_inject is typically used for sending packets, here we just demonstrate input usage
    if (size > 0) {
        pcap_inject(pcap_handle, data, size);
    }

    // Call the function-under-test
    int major_version = pcap_major_version(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}