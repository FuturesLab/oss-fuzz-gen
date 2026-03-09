#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>
#include <string.h>

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    pcap_t *pcap;
    struct bpf_program fp;
    char errbuf[PCAP_ERRBUF_SIZE];
    int result;

    // Initialize pcap_t
    pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap == NULL) {
        return 0;
    }

    // Initialize bpf_program
    if (size > 0) {
        char *filter_exp = (char *)malloc(size + 1);
        if (filter_exp == NULL) {
            pcap_close(pcap);
            return 0;
        }
        memcpy(filter_exp, data, size);
        filter_exp[size] = '\0';

        if (pcap_compile(pcap, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
            free(filter_exp);
            pcap_close(pcap);
            return 0;
        }
        free(filter_exp);
    } else {
        pcap_close(pcap);
        return 0;
    }

    // Call the function-under-test
    result = pcap_setfilter(pcap, &fp);

    // Clean up
    pcap_freecode(&fp);
    pcap_close(pcap);

    return 0;
}