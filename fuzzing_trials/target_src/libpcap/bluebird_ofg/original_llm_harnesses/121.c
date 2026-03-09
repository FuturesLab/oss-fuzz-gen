#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    struct bpf_program program;
    program.bf_len = 1; // Set a non-zero length to avoid NULL pointer
    program.bf_insns = (struct bpf_insn *)data; // Cast the data to bpf_insn

    // Call the function-under-test
    pcap_freecode(&program);

    return 0;
}