#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "pcap/pcap.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    struct bpf_program fp;
    bpf_u_int32 netmask = 0xffffff;
    int optimize = 0;
    int compile_result;

    if (!handle) {
        return 0;
    }

    char *filter_exp = (char *)malloc(Size + 1);
    if (!filter_exp) {
        pcap_close(handle);
        return 0;
    }
    memcpy(filter_exp, Data, Size);
    filter_exp[Size] = '\0';

    compile_result = pcap_compile(handle, &fp, filter_exp, optimize, netmask);
    if (compile_result != 0) {
        pcap_geterr(handle);
        free(filter_exp);
        pcap_close(handle);
        return 0;
    }

    if (pcap_setfilter(handle, &fp) != 0) {
        pcap_geterr(handle);
        pcap_freecode(&fp);
        free(filter_exp);
        pcap_close(handle);
        return 0;
    }

    write_dummy_file(Data, Size);


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of pcap_dump_open
    pcap_dumper_t *dumper = pcap_dump_open(handle, (const char *)"r");
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (!dumper) {
        pcap_geterr(handle);
        pcap_freecode(&fp);
        free(filter_exp);
        pcap_close(handle);
        return 0;
    }

    pcap_geterr(handle);

    int link_type = pcap_datalink(handle);

    pcap_dump_close(dumper);
    pcap_freecode(&fp);
    free(filter_exp);
    pcap_close(handle);

    return 0;
}