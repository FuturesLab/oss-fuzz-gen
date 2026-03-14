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

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare pcap_t using pcap_open_dead
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) {
        return 0;
    }

    // Prepare bpf_program
    struct bpf_program bpf;
    memset(&bpf, 0, sizeof(bpf));

    // Null-terminate Data for filter string
    char *filter_exp = (char *)malloc(Size + 1);
    if (!filter_exp) {
        pcap_close(pcap);
        return 0;
    }
    memcpy(filter_exp, Data, Size);
    filter_exp[Size] = '\0';

    // Compile filter
    int compile_result = pcap_compile(pcap, &bpf, filter_exp, 0, PCAP_NETMASK_UNKNOWN);

    // Validate BPF program
    int valid = bpf_validate(bpf.bf_insns, bpf.bf_len);

    // Prepare packet header and data
    struct pcap_pkthdr header;
    header.caplen = Size;
    header.len = Size;
    header.ts.tv_sec = 0;
    header.ts.tv_usec = 0;

    // Use pcap_offline_filter
    int match = pcap_offline_filter(&bpf, &header, Data);

    // Use bpf_filter
    u_int result = bpf_filter(bpf.bf_insns, Data, header.len, header.caplen);

    // Use pcap_compile_nopcap
    struct bpf_program bpf_nopcap;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 4 of pcap_compile_nopcap
    int compile_nopcap_result = pcap_compile_nopcap(65535, DLT_EN10MB, &bpf_nopcap, filter_exp, Size, PCAP_NETMASK_UNKNOWN);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Cleanup
    if (compile_result == 0) {
        pcap_freecode(&bpf);
    }
    if (compile_nopcap_result == 0) {
        pcap_freecode(&bpf_nopcap);
    }
    free(filter_exp);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_freecode to pcap_setfilter

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function pcap_bufsize with pcap_snapshot
        int ret_pcap_bufsize_bfiks = pcap_snapshot(pcap);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_pcap_bufsize_bfiks < 0){
        	return 0;
        }

        int ret_pcap_setfilter_bzeog = pcap_setfilter(pcap, &bpf);
        if (ret_pcap_setfilter_bzeog < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    pcap_close(pcap);

    return 0;
}