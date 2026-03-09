// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// bpf_validate at bpf_filter.c:541:1 in bpf.h
// pcap_close at pcap.c:4247:1 in pcap.h
// bpf_dump at bpf_dump.c:30:1 in bpf.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <bpf.h>

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct bpf_insn)) {
        return 0;
    }

    // Prepare a dummy pcap_t handle
    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap_handle) {
        return 0;
    }

    // Invoke pcap_geterr to get error message
    char *err_msg = pcap_geterr(pcap_handle);
    if (err_msg) {
        printf("Error: %s\n", err_msg);
    }

    // Prepare BPF instructions and validate them
    struct bpf_insn *bpf_insns = (struct bpf_insn *)Data;
    int insn_count = Size / sizeof(struct bpf_insn);
    int is_valid = bpf_validate(bpf_insns, insn_count);
    if (!is_valid) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Prepare a BPF program
    struct bpf_program bpf_prog;
    bpf_prog.bf_len = insn_count;
    bpf_prog.bf_insns = bpf_insns;

    // Dump the BPF program
    bpf_dump(&bpf_prog, 2);

    // Prepare a dummy pcap_pkthdr and packet data
    struct pcap_pkthdr pkthdr;
    pkthdr.caplen = Size;
    pkthdr.len = Size;
    const u_char *packet_data = Data;

    // Write dummy file for pcap_next_ex usage
    write_dummy_file(Data, Size);

    // Invoke pcap_next_ex
    struct pcap_pkthdr *header;
    const u_char *pkt_data;
    int res = pcap_next_ex(pcap_handle, &header, &pkt_data);
    if (res == PCAP_ERROR) {
        err_msg = pcap_geterr(pcap_handle);
        if (err_msg) {
            printf("Error: %s\n", err_msg);
        }
    }

    // Invoke pcap_offline_filter
    int match = pcap_offline_filter(&bpf_prog, &pkthdr, packet_data);
    printf("Filter match: %d\n", match);

    // Clean up
    pcap_close(pcap_handle);
    return 0;
}