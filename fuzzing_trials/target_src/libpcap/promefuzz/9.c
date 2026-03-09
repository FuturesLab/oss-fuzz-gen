// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_perror at pcap.c:3608:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_perror at pcap.c:3608:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_perror at pcap.c:3608:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINKTYPE_ETHERNET 1
#define SNAPLEN 65535
#define OPTIMIZE 1
#define NETMASK 0xFFFFFF00

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    write_dummy_file(Data, Size);

    pcap_t *handle = pcap_open_dead(LINKTYPE_ETHERNET, SNAPLEN);
    if (handle == NULL) {
        return 0;
    }

    struct bpf_program fp;
    char filter_exp[] = "tcp";
    int compile_result = pcap_compile(handle, &fp, filter_exp, OPTIMIZE, NETMASK);
    if (compile_result == -1) {
        pcap_perror(handle, "pcap_compile failed");
        pcap_close(handle);
        return 0;
    }

    int setfilter_result = pcap_setfilter(handle, &fp);
    if (setfilter_result == -1) {
        pcap_perror(handle, "pcap_setfilter failed");
        pcap_freecode(&fp);
        pcap_close(handle);
        return 0;
    }

    pcap_perror(handle, "No error");

    pcap_freecode(&fp);
    pcap_close(handle);

    return 0;
}