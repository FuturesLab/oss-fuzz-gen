// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_set_tstamp_type at pcap.c:2635:1 in pcap.h
// pcap_tstamp_type_val_to_description at pcap.c:3508:1 in pcap.h
// pcap_tstamp_type_name_to_val at pcap.c:3484:1 in pcap.h
// pcap_list_tstamp_types at pcap.c:492:1 in pcap.h
// pcap_set_tstamp_precision at pcap.c:2704:1 in pcap.h
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
#include <stdio.h>

#define DUMMY_FILE "./dummy_file"

static void cleanup(pcap_t *handle, int *tstamp_types) {
    if (handle) {
        pcap_close(handle);
    }
    if (tstamp_types) {
        free(tstamp_types);
    }
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create(DUMMY_FILE, errbuf);
    if (handle == NULL) {
        return 0;
    }

    // Test pcap_set_tstamp_type
    int tstamp_type = Data[0];
    pcap_set_tstamp_type(handle, tstamp_type);

    // Test pcap_tstamp_type_val_to_description
    const char *desc = pcap_tstamp_type_val_to_description(tstamp_type);

    // Test pcap_tstamp_type_name_to_val
    char tstamp_name[256];
    snprintf(tstamp_name, sizeof(tstamp_name), "name_%d", tstamp_type);
    int tstamp_val = pcap_tstamp_type_name_to_val(tstamp_name);

    // Test pcap_list_tstamp_types
    int *tstamp_types = NULL;
    int count = pcap_list_tstamp_types(handle, &tstamp_types);
    if (count > 0) {
        free(tstamp_types);
        tstamp_types = NULL; // Avoid double-free by nullifying the pointer
    }

    // Test pcap_set_tstamp_precision
    int precision = (Size > 1) ? Data[1] : 0;
    pcap_set_tstamp_precision(handle, precision);

    // Test pcap_tstamp_type_val_to_name
    const char *name = pcap_tstamp_type_val_to_name(tstamp_type);

    cleanup(handle, tstamp_types);

    return 0;
}