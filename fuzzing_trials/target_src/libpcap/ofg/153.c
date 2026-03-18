#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract parameters
    if (size < 5) return 0;

    // Extract parameters from data
    const char *device = "eth0"; // Use a default non-NULL device name
    int snaplen = (int)data[0];  // Use the first byte for snaplen
    int promisc = (int)data[1];  // Use the second byte for promisc
    int to_ms = (int)data[2];    // Use the third byte for to_ms
    char errbuf[PCAP_ERRBUF_SIZE];
    
    // Ensure errbuf is not NULL
    memset(errbuf, 0, sizeof(errbuf));

    // Call the function-under-test
    pcap_t *handle = pcap_open_live(device, snaplen, promisc, to_ms, errbuf);

    // Clean up if handle is not NULL
    if (handle != NULL) {
        pcap_close(handle);
    }

    return 0;
}