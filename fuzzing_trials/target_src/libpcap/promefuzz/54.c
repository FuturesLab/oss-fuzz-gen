// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <bpf.h>
#include <unistd.h>

static void initialize_bpf_program(struct bpf_program *prog) {
    prog->bf_len = 1;
    prog->bf_insns = malloc(sizeof(struct bpf_insn) * prog->bf_len);
    if (prog->bf_insns) {
        prog->bf_insns[0].code = BPF_RET | BPF_K;
        prog->bf_insns[0].jt = 0;
        prog->bf_insns[0].jf = 0;
        prog->bf_insns[0].k = 0;
    }
}

static void cleanup_bpf_program(struct bpf_program *prog) {
    if (prog->bf_insns) {
        free(prog->bf_insns);
        prog->bf_insns = NULL;
    }
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct bpf_insn)) {
        return 0;
    }

    struct bpf_program prog;
    initialize_bpf_program(&prog);

    // Fuzz bpf_dump
    bpf_dump(&prog, Data[0] % 4);

    // Fuzz pcap_freecode
    pcap_freecode(&prog);

    // Reinitialize the program
    initialize_bpf_program(&prog);

    // Fuzz bpf_validate
    int valid = bpf_validate(prog.bf_insns, prog.bf_len);

    // Fuzz bpf_image
    char *image = bpf_image(prog.bf_insns, prog.bf_len);
    // Do not free image as it is managed by libpcap

    // Prepare pcap_t and pcap_pkthdr
    pcap_t *pcap = pcap_open_dead(DLT_RAW, 65535);
    struct pcap_pkthdr pkthdr;
    pkthdr.caplen = Size;
    pkthdr.len = Size;
    pkthdr.ts.tv_sec = 0;
    pkthdr.ts.tv_usec = 0;

    // Fuzz pcap_setfilter
    if (pcap) {
        pcap_setfilter(pcap, &prog);
        pcap_close(pcap);
    }

    // Fuzz pcap_offline_filter
    if (valid) {
        pcap_offline_filter(&prog, &pkthdr, Data);
    }

    cleanup_bpf_program(&prog);
    return 0;
}