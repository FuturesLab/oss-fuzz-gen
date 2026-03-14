// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_list_datalinks at pcap.c:3018:1 in pcap.h
// pcap_set_datalink at pcap.c:3068:1 in pcap.h
// pcap_datalink at pcap.c:3002:1 in pcap.h
// pcap_free_datalinks at pcap.c:3062:1 in pcap.h
// pcap_list_tstamp_types at pcap.c:492:1 in pcap.h
// pcap_free_tstamp_types at pcap.c:534:1 in pcap.h
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

static pcap_t *create_and_activate_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create("any", errbuf);
    if (!handle) return NULL;

    if (pcap_activate(handle) != 0) {
        pcap_close(handle);
        return NULL;
    }
    return handle;
}

int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    pcap_t *handle = create_and_activate_pcap();
    if (!handle) return 0;

    int *dlt_list = NULL;
    int result = pcap_list_datalinks(handle, &dlt_list);
    if (result >= 0) {
        for (int i = 0; i < result; i++) {
            pcap_set_datalink(handle, dlt_list[i]);
            pcap_datalink(handle);
        }
        pcap_free_datalinks(dlt_list);
    }

    int *tstamp_type_list = NULL;
    result = pcap_list_tstamp_types(handle, &tstamp_type_list);
    if (result > 0) {
        pcap_free_tstamp_types(tstamp_type_list);
    }

    pcap_close(handle);
    return 0;
}