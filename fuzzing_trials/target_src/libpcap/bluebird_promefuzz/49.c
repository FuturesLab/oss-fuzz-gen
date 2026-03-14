#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>
#include "pcap/pcap.h"
#include "/src/libpcap/pcap/bpf.h"
#include "string.h"
#include "unistd.h"

static pcap_t* create_dummy_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of pcap_open_dead
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 64);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
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


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_close to pcap_compile
        char* ret_pcap_geterr_xrssi = pcap_geterr(handle);
        if (ret_pcap_geterr_xrssi == NULL){
        	return 0;
        }
        struct bpf_program zqfzdpkv;
        memset(&zqfzdpkv, 0, sizeof(zqfzdpkv));

        int ret_pcap_compile_uleln = pcap_compile(handle, &zqfzdpkv, ret_pcap_geterr_xrssi, 0, 0);
        if (ret_pcap_compile_uleln < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    pcap_close(handle);
    return 0;
}