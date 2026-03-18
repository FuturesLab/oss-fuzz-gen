// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// bpf_validate at bpf_filter.c:541:1 in bpf.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// bpf_dump at bpf_dump.c:30:1 in bpf.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
// bpf_image at bpf_image.c:130:1 in bpf.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <bpf.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_68(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct bpf_insn)) {
        return 0;
    }

    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap_handle) {
        return 0;
    }

    struct bpf_program bpf_prog;
    bpf_prog.bf_len = Size / sizeof(struct bpf_insn);
    bpf_prog.bf_insns = (struct bpf_insn *)malloc(Size);
    if (!bpf_prog.bf_insns) {
        pcap_close(pcap_handle);
        return 0;
    }
    memcpy(bpf_prog.bf_insns, Data, Size);

    if (bpf_validate(bpf_prog.bf_insns, bpf_prog.bf_len)) {
        if (pcap_setfilter(pcap_handle, &bpf_prog) == 0) {
            bpf_dump(&bpf_prog, 3);

            struct pcap_pkthdr pkt_header;
            pkt_header.caplen = Size;
            pkt_header.len = Size;

            if (Size > sizeof(struct pcap_pkthdr)) {
                const u_char *pkt_data = Data + sizeof(struct pcap_pkthdr);
                pcap_offline_filter(&bpf_prog, &pkt_header, pkt_data);
            }

            char *image = bpf_image(bpf_prog.bf_insns, bpf_prog.bf_len);
            if (image) {
                printf("%s\n", image);
            }
        }
    }

    pcap_freecode(&bpf_prog);
    pcap_close(pcap_handle);

    write_dummy_file(Data, Size);

    return 0;
}