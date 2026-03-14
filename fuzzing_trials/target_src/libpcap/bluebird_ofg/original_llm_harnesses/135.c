#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

// Remove the extern "C" linkage specification as it is not needed in a C file
int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < sizeof(struct bpf_program) + sizeof(struct pcap_pkthdr)) {
        return 0;
    }

    // Initialize bpf_program
    struct bpf_program bpf_prog;
    // For fuzzing purposes, we will assume a simple filter with one instruction
    struct bpf_insn insns[] = {
        BPF_STMT(BPF_RET | BPF_K, 0) // Return 0 (drop packet)
    };
    bpf_prog.bf_len = 1;
    bpf_prog.bf_insns = insns;

    // Initialize pcap_pkthdr
    struct pcap_pkthdr pkthdr;
    pkthdr.caplen = size - sizeof(struct bpf_program) - sizeof(struct pcap_pkthdr);
    pkthdr.len = pkthdr.caplen;

    // Set the packet data to the remaining part of the input data
    const u_char *packet_data = data + sizeof(struct bpf_program) + sizeof(struct pcap_pkthdr);

    // Call the function-under-test
    int result = pcap_offline_filter(&bpf_prog, &pkthdr, packet_data);

    // Return the result
    return result;
}