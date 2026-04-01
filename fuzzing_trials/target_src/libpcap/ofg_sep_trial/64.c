#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = NULL;
    struct bpf_program fp;
    char filter_exp[] = "tcp"; // Example filter expression

    // Initialize the pcap handle
    handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (handle == NULL) {
        return 0;
    }

    // Initialize the bpf_program structure
    memset(&fp, 0, sizeof(fp));

    // Compile the filter expression
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        pcap_close(handle);
        return 0;
    }

    // Call the function-under-test
    int result = pcap_setfilter(handle, &fp);

    // Clean up
    pcap_freecode(&fp);
    pcap_close(handle);

    return 0;
}