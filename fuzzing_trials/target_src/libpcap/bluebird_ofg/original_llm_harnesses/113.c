#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    char *device = NULL;

    if (size > 0) {
        // Ensure the data is null-terminated and fits within the buffer
        size_t copy_size = size < PCAP_ERRBUF_SIZE - 1 ? size : PCAP_ERRBUF_SIZE - 1;
        memcpy(errbuf, data, copy_size);
        errbuf[copy_size] = '\0';

        // Call the function-under-test
        device = pcap_lookupdev(errbuf);
    }

    return 0;
}