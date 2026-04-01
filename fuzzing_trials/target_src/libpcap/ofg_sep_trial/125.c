#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int promisc;

    // Ensure that data is large enough to extract an integer for promisc
    if (size < sizeof(int)) {
        return 0;
    }

    // Open a fake pcap handle using pcap_open_dead for testing
    handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (handle == NULL) {
        return 0;
    }

    // Use the first bytes of the data as the promisc parameter
    memcpy(&promisc, data, sizeof(int));

    // Call the function-under-test
    pcap_set_promisc(handle, promisc);

    // Clean up
    pcap_close(handle);

    return 0;
}