// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// bpf_validate at bpf_filter.c:541:1 in bpf.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// bpf_dump at bpf_dump.c:30:1 in bpf.h
// bpf_image at bpf_image.c:130:1 in bpf.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pcap.h>
#include <bpf.h>
#include <string.h>
#include <unistd.h>

static pcap_t* create_dummy_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!handle) {
        fprintf(stderr, "Failed to open pcap handle: %s\n", errbuf);
        return NULL;
    }
    return handle;
}

static struct bpf_program compile_dummy_filter(pcap_t *handle, const char *filter_exp) {
    struct bpf_program fp;
    memset(&fp, 0, sizeof(fp)); // Initialize to zero to avoid uninitialized usage
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Failed to compile filter: %s\n", pcap_geterr(handle));
        fp.bf_len = 0;
        fp.bf_insns = NULL;
    }
    return fp;
}

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct bpf_insn)) {
        return 0;
    }

    pcap_t *handle = create_dummy_pcap();
    if (!handle) {
        return 0;
    }

    struct bpf_program fp = compile_dummy_filter(handle, "tcp");
    if (fp.bf_len == 0) {
        pcap_close(handle);
        return 0;
    }

    struct bpf_insn *insns = (struct bpf_insn *)Data;
    int insn_count = Size / sizeof(struct bpf_insn);

    if (bpf_validate(insns, insn_count)) {
        if (pcap_setfilter(handle, &fp) != 0) {
            fprintf(stderr, "Failed to set filter: %s\n", pcap_geterr(handle));
        }

        bpf_dump(&fp, 3);
        char *image = bpf_image(insns, insn_count);
        if (image) {
            printf("BPF Image: %s\n", image);
        }

        struct pcap_pkthdr header;
        header.caplen = Size;
        header.len = Size;
        int match = pcap_offline_filter(&fp, &header, Data);
        printf("Packet match: %d\n", match);
    }

    pcap_freecode(&fp); // Free the compiled filter to avoid memory leak

    write_dummy_file(Data, Size);

    pcap_close(handle);
    return 0;
}