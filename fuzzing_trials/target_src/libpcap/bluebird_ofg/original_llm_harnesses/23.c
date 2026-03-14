#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    int nonblock;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Initialize pcap_handle with pcap_open_dead for fuzzing purposes
    pcap_handle = pcap_open_dead(DLT_RAW, 65535);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Use the first byte of data to determine the nonblock parameter
    if (size > 0) {
        nonblock = data[0] % 2; // 0 or 1
    } else {
        nonblock = 0; // Default to non-blocking
    }

    // Call the function under test
    pcap_setnonblock(pcap_handle, nonblock, errbuf);

    // Clean up
    pcap_close(pcap_handle);

    return 0;
}