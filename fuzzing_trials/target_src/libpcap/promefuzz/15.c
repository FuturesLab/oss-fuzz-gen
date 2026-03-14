// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_dump_open at sf-pcap.c:895:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_datalink at pcap.c:3002:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1255:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static pcap_t *initialize_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!handle) {
        fprintf(stderr, "pcap_open_dead failed: %s\n", errbuf);
    }
    return handle;
}

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pcap_t *handle = initialize_pcap();
    if (!handle) return 0;

    struct bpf_program fp;
    char filter_exp[256];
    if (Size < sizeof(filter_exp)) {
        memcpy(filter_exp, Data, Size);
        filter_exp[Size] = '\0';
    } else {
        return 0;
    }

    bpf_u_int32 net = 0;
    int optimize = 1;

    if (pcap_compile(handle, &fp, filter_exp, optimize, net) == -1) {
        pcap_geterr(handle);
        pcap_close(handle);
        return 0;
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        pcap_geterr(handle);
        pcap_freecode(&fp);
        pcap_close(handle);
        return 0;
    }

    pcap_freecode(&fp);

    FILE *dummy_file = fopen("./dummy_file", "w");
    if (!dummy_file) {
        pcap_close(handle);
        return 0;
    }
    fclose(dummy_file);

    pcap_dumper_t *dumper = pcap_dump_open(handle, "./dummy_file");
    if (!dumper) {
        pcap_geterr(handle);
        pcap_close(handle);
        return 0;
    }

    pcap_geterr(handle);
    pcap_datalink(handle);

    pcap_dump_close(dumper);
    pcap_close(handle);

    return 0;
}