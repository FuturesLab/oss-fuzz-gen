#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Initialize parameters for pcap_compile_nopcap
    int snaplen = 65535;  // Typical maximum capture length
    int linktype = DLT_EN10MB;  // Ethernet link type
    struct bpf_program fp;
    char *filter_exp = (char *)malloc(size + 1);
    int optimize = 1;  // Enable optimizations
    bpf_u_int32 netmask = PCAP_NETMASK_UNKNOWN;  // Unknown netmask

    // Ensure the filter expression is null-terminated
    memcpy(filter_exp, data, size);
    filter_exp[size] = '\0';

    // Call the function-under-test
    int result = pcap_compile_nopcap(snaplen, linktype, &fp, filter_exp, optimize, netmask);

    // Clean up
    if (result == 0) {
        pcap_freecode(&fp);
    }
    free(filter_exp);

    return 0;
}