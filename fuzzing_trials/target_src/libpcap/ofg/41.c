#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    pcap_if_t *alldevs = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Ensure errbuf is null-terminated
    memset(errbuf, 0, PCAP_ERRBUF_SIZE);

    // Call the function-under-test
    int result = pcap_findalldevs(&alldevs, errbuf);

    // Clean up
    if (alldevs != NULL) {
        pcap_freealldevs(alldevs);
    }

    return 0;
}