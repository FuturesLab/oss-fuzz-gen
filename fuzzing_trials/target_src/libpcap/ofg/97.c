#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Use pcap_open_offline_with_tstamp_precision to create a pcap handle from input data
    // This requires that the input data is treated as a file stream
    FILE *f = fmemopen((void *)data, size, "rb");
    if (f == NULL) {
        return 0;
    }

    pcap_handle = pcap_fopen_offline(f, errbuf);
    if (pcap_handle == NULL) {
        fclose(f);
        return 0;
    }

    // Call the function-under-test
    int fd = pcap_fileno(pcap_handle);

    // Clean up
    pcap_close(pcap_handle);
    fclose(f);

    return 0;
}