#include <pcap/pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    // Define and initialize parameters for pcap_compile_nopcap
    int snaplen = 65535; // Standard maximum capture length
    int dlt = DLT_EN10MB; // Ethernet link layer
    struct bpf_program fp; // BPF program structure
    char filter_exp[256]; // Filter expression buffer
    int optimize = 1; // Enable optimization
    bpf_u_int32 netmask = 0xFFFFFF00; // Default netmask for a class C network

    // Ensure the filter expression is null-terminated and within buffer size
    size_t filter_exp_len = (size < sizeof(filter_exp) - 1) ? size : sizeof(filter_exp) - 1;
    memcpy(filter_exp, data, filter_exp_len);
    filter_exp[filter_exp_len] = '\0';

    // Call the function-under-test
    int result = pcap_compile_nopcap(snaplen, dlt, &fp, filter_exp, optimize, netmask);

    // Free the allocated memory for the BPF program
    if (result == 0) {
        pcap_freecode(&fp);
    }

    return 0;
}