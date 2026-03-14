#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to construct the necessary structures
    if (size < sizeof(struct bpf_program) + sizeof(struct pcap_pkthdr)) {
        return 0;
    }

    // Initialize a bpf_program structure
    struct bpf_program bpf;
    bpf.bf_len = 1; // Set a minimal length for the filter
    bpf.bf_insns = (struct bpf_insn *)data; // Use the input data as instructions

    // Initialize a pcap_pkthdr structure
    struct pcap_pkthdr pkthdr;
    pkthdr.ts.tv_sec = 0;
    pkthdr.ts.tv_usec = 0;
    pkthdr.caplen = size;
    pkthdr.len = size;

    // Use the remaining data as packet data
    const u_char *packet = data + sizeof(struct bpf_program);

    // Call the function-under-test
    int result = pcap_offline_filter(&bpf, &pkthdr, packet);

    // Return the result
    return result;
}