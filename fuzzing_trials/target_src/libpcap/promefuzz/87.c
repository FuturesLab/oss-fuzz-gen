// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
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

static void fuzz_pcap_compile(pcap_t *handle, const char *filter_expr) {
    struct bpf_program fp;
    bpf_u_int32 netmask = 0xffffff00;
    if (pcap_compile(handle, &fp, filter_expr, 0, netmask) == 0) {
        bpf_dump(&fp, 2);
        pcap_setfilter(handle, &fp);
        pcap_freecode(&fp);
    }
}

static void fuzz_bpf_functions(const struct bpf_program *fp) {
    bpf_dump(fp, 1);
    if (fp->bf_len > 0) {
        char *image = bpf_image(fp->bf_insns, fp->bf_len);
        if (image) {
            printf("BPF Image: %s\n", image);
        }
        bpf_validate(fp->bf_insns, fp->bf_len);
    }
}

int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pcap_t *handle = initialize_pcap();
    if (!handle) return 0;

    char *filter_expr = (char *)malloc(Size + 1);
    if (!filter_expr) {
        cleanup_pcap(handle);
        return 0;
    }
    memcpy(filter_expr, Data, Size);
    filter_expr[Size] = '\0';

    fuzz_pcap_compile(handle, filter_expr);

    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter_expr, 0, 0xffffff00) == 0) {
        fuzz_bpf_functions(&fp);
        pcap_freecode(&fp);
    }

    free(filter_expr);
    cleanup_pcap(handle);
    return 0;
}