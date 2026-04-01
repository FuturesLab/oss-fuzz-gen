#include <stddef.h>
#include <stdint.h>
#include "/src/libbpf/src/libbpf.h"

// Use the existing enumeration type from bpf.h
typedef enum bpf_prog_type DW_TAG_enumeration_typebpf_prog_type;

extern int libbpf_probe_bpf_prog_type(DW_TAG_enumeration_typebpf_prog_type prog_type, const void *opts);

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    if (size < sizeof(DW_TAG_enumeration_typebpf_prog_type)) {
        return 0;
    }

    // Extract the bpf_prog_type from the input data
    DW_TAG_enumeration_typebpf_prog_type prog_type = *(DW_TAG_enumeration_typebpf_prog_type *)data;

    // Ensure prog_type is within valid range
    if (prog_type > BPF_PROG_TYPE_SYSCALL) {
        prog_type = BPF_PROG_TYPE_UNSPEC;
    }

    // Call the function-under-test
    int result = libbpf_probe_bpf_prog_type(prog_type, (const void *)(data + sizeof(DW_TAG_enumeration_typebpf_prog_type)));

    return 0;
}