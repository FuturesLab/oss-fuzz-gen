#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    int snaplen = 65535; // typical maximum capture length
    int linktype = DLT_EN10MB; // Ethernet
    struct bpf_program fp;
    int optimize = 1; // enable optimization
    bpf_u_int32 netmask = 0xFFFFFF00; // typical netmask for a local network

    // Allocate memory for the filter expression and ensure it's null-terminated
    char *filter_exp = (char *)malloc(size + 1);
    if (filter_exp == NULL) {
        return 0;
    }
    memcpy(filter_exp, data, size);
    filter_exp[size] = '\0';

    // Call the function-under-test
    pcap_compile_nopcap(snaplen, linktype, &fp, filter_exp, optimize, netmask);

    // Clean up
    free(filter_exp);
    pcap_freecode(&fp);

    return 0;
}