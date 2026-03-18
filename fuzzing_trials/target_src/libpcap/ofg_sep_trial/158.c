#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    int snaplen = 65535;   // Standard maximum capture length
    int linktype = DLT_EN10MB;  // Ethernet
    struct bpf_program fp;
    char filter_exp[256];
    int optimize = 1;
    bpf_u_int32 netmask = 0xffffff;  // Default netmask

    // Ensure the filter expression is null-terminated and not too long
    size_t filter_exp_length = size < 255 ? size : 255;
    memcpy(filter_exp, data, filter_exp_length);
    filter_exp[filter_exp_length] = '\0';

    // Call the function-under-test
    if (pcap_compile_nopcap(snaplen, linktype, &fp, filter_exp, optimize, netmask) == -1) {
        return 0;
    }

    // Free the compiled program if it was allocated
    pcap_freecode(&fp);

    return 0;
}