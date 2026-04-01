// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_next_ex at pcap.c:568:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
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

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    // Write data to dummy file for pcap_open_offline
    write_dummy_file(Data, Size);

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline("./dummy_file", errbuf);
    if (!handle) {
        return 0; // Unable to open file, skip this input
    }

    // pcap_geterr
    char *error = pcap_geterr(handle);
    if (error) {
        printf("Error: %s\n", error);
    }

    // Prepare a dummy bpf_program and bpf_insn for bpf_validate and bpf_dump
    struct bpf_insn dummy_insns[1] = {{0}};
    struct bpf_program dummy_program = {1, dummy_insns};

    // bpf_validate
    int valid = bpf_validate(dummy_program.bf_insns, dummy_program.bf_len);
    printf("BPF validation: %s\n", valid ? "valid" : "invalid");

    // bpf_dump
    bpf_dump(&dummy_program, 2);

    // pcap_next_ex
    struct pcap_pkthdr *pkt_header;
    const u_char *pkt_data;
    int result = pcap_next_ex(handle, &pkt_header, &pkt_data);
    if (result == PCAP_ERROR) {
        printf("Error reading packet: %s\n", pcap_geterr(handle));
    }

    // pcap_geterr again after pcap_next_ex
    error = pcap_geterr(handle);
    if (error) {
        printf("Error after pcap_next_ex: %s\n", error);
    }

    // pcap_offline_filter
    int match = pcap_offline_filter(&dummy_program, pkt_header, pkt_data);
    printf("Offline filter match: %d\n", match);

    pcap_close(handle);
    return 0;
}