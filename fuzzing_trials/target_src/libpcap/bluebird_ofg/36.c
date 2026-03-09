#include <stdint.h>
#include "stdlib.h"
#include "pcap/pcap.h"

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    // Initialize variables
    pcap_t *p = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a pcap handle for testing
    p = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet link type, max snaplen

    // Ensure the data is not null and has a valid size
    if (data != NULL && size > 0) {
        // Call the function-under-test
        int result = pcap_getnonblock(p, errbuf);
    }

    // Clean up
    if (p != NULL) {
        pcap_close(p);
    }

    return 0;
}