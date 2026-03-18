#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    pcap_t *pcap;
    struct bpf_program fp;
    char errbuf[PCAP_ERRBUF_SIZE];
    const char *filter_exp = "tcp";
    int optimize = 1;
    bpf_u_int32 net = 0;

    // Check if the size is sufficient for creating a dummy device name
    if (size < 10) {
        return 0;
    }

    // Create a dummy device name from the input data
    char dev_name[10];
    memcpy(dev_name, data, 9);
    dev_name[9] = '\0';

    // Open a pcap handle on the dummy device
    pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) {
        return 0;
    }

    // Compile the filter expression
    int result = pcap_compile(pcap, &fp, filter_exp, optimize, net);

    // Clean up
    pcap_close(pcap);
    if (fp.bf_insns != NULL) {
        pcap_freecode(&fp);
    }

    return 0;
}