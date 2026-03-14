#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

// Function to be used by the fuzzer
int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the headers
    if (size < sizeof(struct bpf_program) + sizeof(struct pcap_pkthdr)) {
        return 0;
    }

    // Initialize bpf_program
    struct bpf_program bpf_prog;
    bpf_prog.bf_len = 1; // Set a non-zero length
    struct bpf_insn insn = { 0 }; // Initialize a bpf instruction
    bpf_prog.bf_insns = &insn; // Point to the instruction

    // Initialize pcap_pkthdr
    struct pcap_pkthdr pkthdr;
    pkthdr.caplen = size - sizeof(struct bpf_program) - sizeof(struct pcap_pkthdr);
    pkthdr.len = pkthdr.caplen; // Set the packet length to the captured length

    // Initialize packet data
    const u_char *packet_data = data + sizeof(struct bpf_program) + sizeof(struct pcap_pkthdr);

    // Call the function under test
    int result = pcap_offline_filter(&bpf_prog, &pkthdr, packet_data);

    (void)result; // Suppress unused variable warning

    return 0;
}