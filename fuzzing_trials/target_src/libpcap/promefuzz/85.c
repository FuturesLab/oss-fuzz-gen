// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
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
#include <stdio.h>
#include <unistd.h>

static void write_dummy_file(const char *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize pcap_t
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) {
        return 0;
    }

    // Initialize bpf_program
    struct bpf_program fp;
    memset(&fp, 0, sizeof(fp));

    // Prepare a filter expression
    char *filter_exp = "tcp";
    if (Size > 1) {
        // Allocate a buffer and ensure it's null-terminated
        filter_exp = (char *)malloc(Size + 1);
        if (!filter_exp) {
            pcap_close(pcap);
            return 0;
        }
        memcpy(filter_exp, Data, Size);
        filter_exp[Size] = '\0'; // Null-terminate
    }

    // Compile the filter
    int optimize = 1;
    bpf_u_int32 netmask = 0xFFFFFF00; // Assuming class C network
    if (pcap_compile(pcap, &fp, filter_exp, optimize, netmask) == -1) {
        if (filter_exp != "tcp") free(filter_exp);
        pcap_close(pcap);
        return 0;
    }

    // Set the filter
    if (pcap_setfilter(pcap, &fp) == -1) {
        pcap_freecode(&fp);
        if (filter_exp != "tcp") free(filter_exp);
        pcap_close(pcap);
        return 0;
    }

    // BPF Dump
    bpf_dump(&fp, Data[0] % 3);

    // BPF Validate
    if (fp.bf_len > 0 && fp.bf_insns) {
        bpf_validate(fp.bf_insns, fp.bf_len);
    }

    // BPF Image
    if (fp.bf_len > 0 && fp.bf_insns) {
        char *image = bpf_image(fp.bf_insns, fp.bf_len);
        if (image) {
            free(image);
        }
    }

    // Prepare dummy packet for pcap_offline_filter
    struct pcap_pkthdr header;
    header.caplen = Size;
    header.len = Size;
    const u_char *packet = Data;

    // pcap_offline_filter
    pcap_offline_filter(&fp, &header, packet);

    // Cleanup
    pcap_freecode(&fp);
    if (filter_exp != "tcp") free(filter_exp);
    pcap_close(pcap);

    return 0;
}