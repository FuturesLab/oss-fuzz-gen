// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <bpf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static pcap_t *initialize_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!handle) {
        fprintf(stderr, "Failed to open pcap handle: %s\n", errbuf);
        return NULL;
    }
    return handle;
}

static void cleanup_pcap(pcap_t *handle) {
    if (handle) {
        pcap_close(handle);
    }
}

static struct bpf_program compile_filter(pcap_t *handle, const char *filter_exp, bpf_u_int32 netmask) {
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter_exp, 0, netmask) == -1) {
        fprintf(stderr, "Failed to compile filter: %s\n", pcap_geterr(handle));
    }
    return fp;
}

static void apply_filter(pcap_t *handle, struct bpf_program *fp) {
    if (pcap_setfilter(handle, fp) == -1) {
        fprintf(stderr, "Failed to set filter: %s\n", pcap_geterr(handle));
    }
}

static void dump_bpf_program(struct bpf_program *fp, int option) {
    bpf_dump(fp, option);
}

static void free_bpf_program(struct bpf_program *fp) {
    pcap_freecode(fp);
}

static void test_bpf_image(struct bpf_insn *insns, int len) {
    char *image = bpf_image(insns, len);
    if (image) {
        printf("BPF Image: %s\n", image);
    }
}

static void validate_bpf_program(struct bpf_insn *insns, int len) {
    if (bpf_validate(insns, len)) {
        printf("BPF program is valid.\n");
    } else {
        printf("BPF program is invalid.\n");
    }
}

int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pcap_t *handle = initialize_pcap();
    if (!handle) return 0;

    const char *filter_exp = "tcp";
    bpf_u_int32 netmask = 0xffffff00;

    struct bpf_program fp = compile_filter(handle, filter_exp, netmask);
    apply_filter(handle, &fp);

    int option = Data[0] % 3; // Randomize option for bpf_dump
    dump_bpf_program(&fp, option);

    if (fp.bf_insns) {
        test_bpf_image(fp.bf_insns, fp.bf_len);
        validate_bpf_program(fp.bf_insns, fp.bf_len);
    }

    free_bpf_program(&fp);
    cleanup_pcap(handle);

    return 0;
}