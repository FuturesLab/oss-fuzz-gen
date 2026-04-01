#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Initialize a pcap_t handle with pcap_create and pcap_activate
    pcap_handle = pcap_create("any", errbuf);
    if (pcap_handle == NULL) {
        return 0;
    }

    if (pcap_activate(pcap_handle) != 0) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Use the first byte of data as the timeout value
    int timeout = (size > 0) ? data[0] : 0;

    // Call the function-under-test
    pcap_set_timeout(pcap_handle, timeout);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}