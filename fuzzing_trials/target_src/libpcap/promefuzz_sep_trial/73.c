// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_set_datalink at pcap.c:3068:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_list_datalinks at pcap.c:3018:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_free_datalinks at pcap.c:3062:1 in pcap.h
// pcap_compile_nopcap at gencode.c:1351:1 in pcap.h
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

static pcap_t* initialize_pcap_handle(char *errbuf) {
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!handle) {
        fprintf(stderr, "Failed to open dead pcap handle: %s\n", errbuf);
    }
    return handle;
}

static void fuzz_pcap_set_datalink(pcap_t *handle, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int dlt = *(int *)Data;
    int result = pcap_set_datalink(handle, dlt);
    if (result != 0) {
        fprintf(stderr, "pcap_set_datalink failed: %s\n", pcap_geterr(handle));
    }
}

static void fuzz_pcap_setfilter(pcap_t *handle, const uint8_t *Data, size_t Size) {
    struct bpf_program fp;
    char filter_exp[256];
    if (Size >= sizeof(filter_exp)) return;
    memcpy(filter_exp, Data, Size);
    filter_exp[Size] = '\0';

    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "pcap_compile failed: %s\n", pcap_geterr(handle));
        return;
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "pcap_setfilter failed: %s\n", pcap_geterr(handle));
    }

    pcap_freecode(&fp);
}

static void fuzz_pcap_list_datalinks(pcap_t *handle) {
    int *dlt_list = NULL;
    int dlt_count = pcap_list_datalinks(handle, &dlt_list);
    if (dlt_count < 0) {
        fprintf(stderr, "pcap_list_datalinks failed: %s\n", pcap_geterr(handle));
    } else {
        pcap_free_datalinks(dlt_list);
    }
}

static void fuzz_pcap_compile_nopcap(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(bpf_u_int32) + sizeof(int)) return;
    int snaplen = *(int *)Data;
    int dlt = *(int *)(Data + sizeof(int));
    const char *filter_exp = (const char *)(Data + sizeof(int) + sizeof(int));
    size_t filter_exp_size = Size - (sizeof(int) + sizeof(int));

    char filter_exp_str[256];
    if (filter_exp_size >= sizeof(filter_exp_str)) return;
    memcpy(filter_exp_str, filter_exp, filter_exp_size);
    filter_exp_str[filter_exp_size] = '\0';

    struct bpf_program fp;
    int result = pcap_compile_nopcap(snaplen, dlt, &fp, filter_exp_str, 0, PCAP_NETMASK_UNKNOWN);
    if (result != 0) {
        fprintf(stderr, "pcap_compile_nopcap failed\n");
    } else {
        pcap_freecode(&fp);
    }
}

int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = initialize_pcap_handle(errbuf);
    if (!handle) return 0;

    fuzz_pcap_set_datalink(handle, Data, Size);
    fuzz_pcap_setfilter(handle, Data, Size);
    fuzz_pcap_list_datalinks(handle);
    fuzz_pcap_compile_nopcap(Data, Size);

    pcap_close(handle);
    return 0;
}