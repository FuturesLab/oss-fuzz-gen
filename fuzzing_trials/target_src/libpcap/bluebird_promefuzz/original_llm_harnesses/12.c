// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_perror at pcap.c:3608:1 in pcap.h
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_perror at pcap.c:3608:1 in pcap.h
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

#define DLT_EN10MB 1
#define SNAP_LEN 65535

static void handle_pcap_error(pcap_t *handle, const char *prefix) {
    if (handle) {
        pcap_perror(handle, prefix);
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Step 1: Prepare a fake pcap_t
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, SNAP_LEN);
    if (!handle) {
        fprintf(stderr, "Failed to open dead pcap\n");
        return 0;
    }

    // Step 2: Compile a filter
    struct bpf_program fp;
    char *filter_exp = (char *)malloc(Size + 1);
    if (!filter_exp) {
        pcap_close(handle);
        return 0;
    }
    memcpy(filter_exp, Data, Size);
    filter_exp[Size] = '\0'; // Ensure null-termination

    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        handle_pcap_error(handle, "pcap_compile");
        free(filter_exp);
        pcap_close(handle);
        return 0;
    }

    // Step 3: Set the filter
    if (pcap_setfilter(handle, &fp) == -1) {
        handle_pcap_error(handle, "pcap_setfilter");
    }

    // Step 4: Use pcap_perror to display any errors
    pcap_perror(handle, "Fuzzing pcap error");

    // Step 5: Cleanup
    pcap_freecode(&fp);
    free(filter_exp);
    pcap_close(handle);

    return 0;
}