// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_free_tstamp_types at pcap.c:534:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_list_tstamp_types at pcap.c:492:1 in pcap.h
// pcap_set_tstamp_type at pcap.c:2635:1 in pcap.h
// pcap_set_rfmon at pcap.c:2617:1 in pcap.h
// pcap_set_tstamp_precision at pcap.c:2704:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
// pcap_open_dead_with_tstamp_precision at pcap.c:4558:1 in pcap.h
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

static void cleanup(pcap_t *handle, int *tstamp_types) {
    if (tstamp_types) {
        pcap_free_tstamp_types(tstamp_types);
    }
    if (handle) {
        pcap_close(handle);
    }
}

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create("any", errbuf);
    if (!handle) {
        return 0;
    }

    int *tstamp_types = NULL;
    int tstamp_type_count = pcap_list_tstamp_types(handle, &tstamp_types);
    if (tstamp_type_count < 0) {
        cleanup(handle, tstamp_types);
        return 0;
    }

    int tstamp_type = (Size > 0) ? Data[0] % tstamp_type_count : 0;
    int result = pcap_set_tstamp_type(handle, tstamp_type);

    int rfmon_mode = (Size > 1) ? Data[1] % 2 : 0;
    result = pcap_set_rfmon(handle, rfmon_mode);

    int tstamp_precision = (Size > 2) ? Data[2] % 2 : 0;
    result = pcap_set_tstamp_precision(handle, tstamp_precision);

    result = pcap_activate(handle);
    if (result < 0) {
        cleanup(handle, tstamp_types);
        return 0;
    }

    pcap_t *dead_handle = pcap_open_dead_with_tstamp_precision(DLT_EN10MB, 65535, tstamp_precision);
    if (dead_handle) {
        pcap_close(dead_handle);
    }

    cleanup(handle, tstamp_types);
    return 0;
}