#include <stdint.h>
#include <stdlib.h>
#include <pcap.h>

// Remove the 'extern "C"' as it is not needed in a C file
int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Ensure there is enough data to avoid accessing out of bounds
    if (size < 4) {
        return 0;
    }

    // Declare and initialize the bpf_program structure
    struct bpf_program prog;
    prog.bf_len = 1;
    prog.bf_insns = (struct bpf_insn *)malloc(sizeof(struct bpf_insn));

    if (prog.bf_insns == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Initialize the bpf_insn structure with some values
    prog.bf_insns[0].code = (uint16_t)(data[0] % 256);
    prog.bf_insns[0].jt = (uint8_t)(data[1] % 256);
    prog.bf_insns[0].jf = (uint8_t)(data[2] % 256);
    prog.bf_insns[0].k = (uint32_t)(data[3] % 256);

    // Call the function-under-test
    pcap_freecode(&prog);

    // Free allocated memory
    free(prog.bf_insns);

    return 0;
}