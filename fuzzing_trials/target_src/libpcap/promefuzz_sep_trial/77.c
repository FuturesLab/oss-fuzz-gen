// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
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

static pcap_t *init_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!handle) {
        fprintf(stderr, "Failed to open pcap handle: %s\n", errbuf);
        return NULL;
    }
    return handle;
}

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pcap_t *handle = init_pcap();
    if (!handle) return 0;

    struct bpf_program fp;
    char filter_exp[256];
    snprintf(filter_exp, sizeof(filter_exp), "tcp port %d", Data[0]);

    int optimize = 1;
    bpf_u_int32 netmask = 0xFFFFFF00;

    if (pcap_compile(handle, &fp, filter_exp, optimize, netmask) == -1) {
        pcap_close(handle);
        return 0;
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        pcap_freecode(&fp);
        pcap_close(handle);
        return 0;
    }

    bpf_dump(&fp, Data[0] % 4);

    if (fp.bf_insns) {
        bpf_image(fp.bf_insns, fp.bf_len);
        bpf_validate(fp.bf_insns, fp.bf_len);
    }

    pcap_freecode(&fp);
    pcap_close(handle);

    write_dummy_file(Data, Size);

    return 0;
}