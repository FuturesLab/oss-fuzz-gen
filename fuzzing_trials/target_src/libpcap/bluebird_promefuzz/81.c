#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "pcap/pcap.h"
#include "/src/libpcap/pcap/bpf.h"

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_next_ex to pcap_set_datalink
    int ret_pcap_minor_version_nwvgx = pcap_minor_version(pcap_handle);
    if (ret_pcap_minor_version_nwvgx < 0){
    	return 0;
    }

    int ret_pcap_set_datalink_ozrpm = pcap_set_datalink(pcap_handle, ret_pcap_minor_version_nwvgx);
    if (ret_pcap_set_datalink_ozrpm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int match = pcap_offline_filter(&bpf_prog, &pkthdr, packet_data);
    printf("Filter match: %d\n", match);

    // Clean up
    pcap_close(pcap_handle);
    return 0;
}