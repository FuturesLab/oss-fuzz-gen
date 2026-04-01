#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Initialize variables
    pcap_t *p;
    struct bpf_program fp;
    char errbuf[PCAP_ERRBUF_SIZE];
    int optimize = 1;
    bpf_u_int32 netmask = 0xFFFFFF00; // Example netmask

    // Create a pcap_t instance using pcap_open_dead for testing
    p = pcap_open_dead(DLT_EN10MB, 65535);
    if (p == NULL) {
        return 0;
    }

    // Copy the data to a null-terminated string
    char *filter_exp = (char *)malloc(size + 1);
    if (filter_exp == NULL) {
        pcap_close(p);
        return 0;
    }
    memcpy(filter_exp, data, size);
    filter_exp[size] = '\0';

    // Call the function-under-test
    pcap_compile(p, &fp, filter_exp, optimize, netmask);

    // Clean up
    free(filter_exp);
    pcap_freecode(&fp);
    pcap_close(p);

    return 0;
}