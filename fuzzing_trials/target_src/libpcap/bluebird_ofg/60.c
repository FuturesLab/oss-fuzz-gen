#include <stdint.h>
#include "stdlib.h"
#include "pcap/pcap.h"

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    int nonblock;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Initialize pcap_handle with a non-NULL value
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max snaplen

    // Ensure that nonblock is either 0 or 1
    if (size > 0) {
        nonblock = data[0] % 2; // Use the first byte to determine nonblock
    } else {
        nonblock = 0; // Default to 0 if size is 0
    }

    // Call the function-under-test
    int result = pcap_setnonblock(pcap_handle, nonblock, errbuf);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}