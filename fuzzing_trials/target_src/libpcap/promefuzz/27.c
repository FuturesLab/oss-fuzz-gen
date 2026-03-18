// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_init at pcap.c:223:1 in pcap.h
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_list_datalinks at pcap.c:3018:1 in pcap.h
// pcap_set_datalink at pcap.c:3068:1 in pcap.h
// pcap_free_datalinks at pcap.c:3062:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile_nopcap at gencode.c:1351:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap;
    int *dlt_list = NULL;
    struct bpf_program fp;

    // Initialize pcap
    if (pcap_init(PCAP_CHAR_ENC_LOCAL, errbuf) != 0) {
        return 0;
    }

    // Create a "dummy" pcap_t using pcap_open_dead
    pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) {
        return 0;
    }

    // Fuzz pcap_list_datalinks
    if (pcap_list_datalinks(pcap, &dlt_list) >= 0) {
        // Fuzz pcap_set_datalink with the first available dlt
        if (dlt_list != NULL) {
            pcap_set_datalink(pcap, dlt_list[0]);
            pcap_free_datalinks(dlt_list);
        }
    }

    // Ensure null-termination for the Data buffer
    char *filter_expr = (char *)malloc(Size + 1);
    if (!filter_expr) {
        pcap_close(pcap);
        return 0;
    }
    memcpy(filter_expr, Data, Size);
    filter_expr[Size] = '\0';

    // Fuzz pcap_compile_nopcap
    if (pcap_compile_nopcap(65535, DLT_EN10MB, &fp, filter_expr, 0, PCAP_NETMASK_UNKNOWN) == 0) {
        // Fuzz pcap_setfilter
        pcap_setfilter(pcap, &fp);
        pcap_freecode(&fp);
    }

    free(filter_expr);

    // Clean up
    pcap_close(pcap);
    return 0;
}