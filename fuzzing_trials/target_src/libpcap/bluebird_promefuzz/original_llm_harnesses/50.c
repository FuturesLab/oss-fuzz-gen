// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// bpf_validate at bpf_filter.c:541:1 in bpf.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
// bpf_dump at bpf_dump.c:30:1 in bpf.h
// bpf_dump at bpf_dump.c:30:1 in bpf.h
// bpf_dump at bpf_dump.c:30:1 in bpf.h
// bpf_dump at bpf_dump.c:30:1 in bpf.h
// bpf_image at bpf_image.c:130:1 in bpf.h
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <bpf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct bpf_insn)) {
        return 0;
    }

    // Allocate memory for BPF instructions to avoid use-after-free
    struct bpf_insn *bpf_insns = malloc(Size);
    if (!bpf_insns) {
        return 0;
    }
    memcpy(bpf_insns, Data, Size);

    // Prepare a BPF program
    struct bpf_program bpf_prog;
    bpf_prog.bf_len = Size / sizeof(struct bpf_insn);
    bpf_prog.bf_insns = bpf_insns;

    // Validate the BPF program
    if (!bpf_validate(bpf_prog.bf_insns, bpf_prog.bf_len)) {
        free(bpf_insns);
        return 0;
    }

    // Create a dummy packet header and data
    struct pcap_pkthdr pkt_header;
    pkt_header.caplen = Size;
    pkt_header.len = Size;
    const u_char *pkt_data = Data;

    // Test pcap_offline_filter
    int filter_result = pcap_offline_filter(&bpf_prog, &pkt_header, pkt_data);

    // Test bpf_dump with different options
    bpf_dump(&bpf_prog, 0);
    bpf_dump(&bpf_prog, 1);
    bpf_dump(&bpf_prog, 2);
    bpf_dump(&bpf_prog, 3);

    // Test bpf_image
    char *image = bpf_image(bpf_prog.bf_insns, bpf_prog.bf_len);
    // No need to free image as bpf_image uses a static buffer

    // Create a dummy pcap_t
    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle) {
        // Test pcap_setfilter
        int setfilter_result = pcap_setfilter(pcap_handle, &bpf_prog);

        // Clean up pcap handle
        pcap_close(pcap_handle);
    }

    // Free BPF program
    pcap_freecode(&bpf_prog);

    // Do not free bpf_insns here as pcap_freecode already frees it
    // free(bpf_insns); // Removed to avoid double-free

    return 0;
}