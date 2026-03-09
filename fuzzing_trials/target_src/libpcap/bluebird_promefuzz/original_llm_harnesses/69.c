// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_tstamp_type_name_to_val at pcap.c:3484:1 in pcap.h
// pcap_list_tstamp_types at pcap.c:492:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_set_tstamp_precision at pcap.c:2704:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_tstamp_type_val_to_description at pcap.c:3508:1 in pcap.h
// pcap_set_tstamp_type at pcap.c:2635:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_tstamp_type_val_to_name at pcap.c:3496:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static pcap_t *create_dummy_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *p = pcap_create("any", errbuf);
    if (p == NULL) {
        return NULL;
    }
    return p;
}

int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz pcap_tstamp_type_name_to_val
    char *name = strndup((const char *)Data, Size);
    if (name != NULL) {
        pcap_tstamp_type_name_to_val(name);
        free(name);
    }

    // Fuzz pcap_list_tstamp_types
    pcap_t *pcap_handle = create_dummy_pcap();
    if (pcap_handle != NULL) {
        int *tstamp_types;
        pcap_list_tstamp_types(pcap_handle, &tstamp_types);
        free(tstamp_types);
        pcap_close(pcap_handle);
    }

    // Fuzz pcap_set_tstamp_precision
    pcap_handle = create_dummy_pcap();
    if (pcap_handle != NULL) {
        int precision = Data[0] % 2; // 0 or 1
        pcap_set_tstamp_precision(pcap_handle, precision);
        pcap_close(pcap_handle);
    }

    // Fuzz pcap_tstamp_type_val_to_description
    int val = (int)Data[0];
    pcap_tstamp_type_val_to_description(val);

    // Fuzz pcap_set_tstamp_type
    pcap_handle = create_dummy_pcap();
    if (pcap_handle != NULL) {
        pcap_set_tstamp_type(pcap_handle, val);
        pcap_close(pcap_handle);
    }

    // Fuzz pcap_tstamp_type_val_to_name
    pcap_tstamp_type_val_to_name(val);

    return 0;
}