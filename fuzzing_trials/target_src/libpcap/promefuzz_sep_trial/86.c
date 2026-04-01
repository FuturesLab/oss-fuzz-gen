// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <bpf.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

static pcap_t* create_dummy_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    return pcap_open_dead(DLT_EN10MB, 65535);
}

static struct bpf_program* create_dummy_bpf_program() {
    struct bpf_program *program = (struct bpf_program *)malloc(sizeof(struct bpf_program));
    if (program) {
        program->bf_len = 0;
        program->bf_insns = NULL;
    }
    return program;
}

static struct bpf_insn* create_dummy_bpf_insn(int len) {
    struct bpf_insn *insns = (struct bpf_insn *)malloc(sizeof(struct bpf_insn) * len);
    if (insns) {
        for (int i = 0; i < len; i++) {
            insns[i].code = BPF_RET | BPF_K;
            insns[i].jt = 0;
            insns[i].jf = 0;
            insns[i].k = 0;
        }
    }
    return insns;
}

int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pcap_t *pcap = create_dummy_pcap();
    if (!pcap) return 0;

    struct bpf_program filter;
    char filter_exp[] = "tcp";
    bpf_u_int32 netmask = 0xffffff;

    // Test pcap_compile
    if (pcap_compile(pcap, &filter, filter_exp, 0, netmask) == PCAP_ERROR) {
        pcap_close(pcap);
        return 0;
    }

    // Test bpf_dump
    bpf_dump(&filter, Data[0]);

    // Test pcap_setfilter
    pcap_setfilter(pcap, &filter);

    // Test bpf_image
    struct bpf_insn *insns = create_dummy_bpf_insn(filter.bf_len);
    if (insns) {
        char *image = bpf_image(insns, filter.bf_len);
        // Do not free 'image' as it is managed internally by bpf_image
        free(insns);
    }

    // Test bpf_validate
    bpf_validate(filter.bf_insns, filter.bf_len);

    // Test pcap_offline_filter
    struct pcap_pkthdr pkthdr;
    pkthdr.caplen = Size;
    pkthdr.len = Size;
    pcap_offline_filter(&filter, &pkthdr, Data);

    // Cleanup
    pcap_freecode(&filter);
    pcap_close(pcap);

    return 0;
}