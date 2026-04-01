// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_dump_open at sf-pcap.c:895:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_datalink at pcap.c:3002:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1255:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
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

    pcap_dumper_t *dumper = pcap_dump_open(handle, "./dummy_file");
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