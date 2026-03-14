// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_set_datalink at pcap.c:3068:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_datalink_val_to_description_or_dlt at pcap.c:3453:1 in pcap.h
// pcap_datalink_val_to_name at pcap.c:3429:1 in pcap.h
// pcap_datalink_name_to_val at pcap.c:3417:1 in pcap.h
// pcap_datalink_val_to_description at pcap.c:3441:1 in pcap.h
// pcap_tstamp_type_val_to_name at pcap.c:3496:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static pcap_t *get_activated_pcap_handle() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (handle == NULL) {
        fprintf(stderr, "Failed to open pcap handle: %s\n", errbuf);
        return NULL;
    }
    return handle;
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pcap_t *handle = get_activated_pcap_handle();
    if (handle == NULL) return 0;

    // Fuzz pcap_set_datalink
    int dlt_type = Data[0];
    int result = pcap_set_datalink(handle, dlt_type);
    if (result != 0) {
        const char *error = pcap_geterr(handle);
        if (error != NULL) {
            fprintf(stderr, "pcap_set_datalink error: %s\n", error);
        }
    }

    // Fuzz pcap_datalink_val_to_description_or_dlt
    const char *description = pcap_datalink_val_to_description_or_dlt(dlt_type);
    if (description != NULL) {
        printf("Description: %s\n", description);
    }

    // Fuzz pcap_datalink_val_to_name
    const char *name = pcap_datalink_val_to_name(dlt_type);
    if (name != NULL) {
        printf("Name: %s\n", name);
    }

    // Fuzz pcap_datalink_name_to_val
    char dlt_name[32];
    snprintf(dlt_name, sizeof(dlt_name), "DLT_%u", dlt_type);
    int dlt_value = pcap_datalink_name_to_val(dlt_name);
    if (dlt_value != -1) {
        printf("DLT value: %d\n", dlt_value);
    }

    // Fuzz pcap_datalink_val_to_description
    const char *dlt_description = pcap_datalink_val_to_description(dlt_type);
    if (dlt_description != NULL) {
        printf("DLT Description: %s\n", dlt_description);
    }

    // Fuzz pcap_tstamp_type_val_to_name
    const char *tstamp_name = pcap_tstamp_type_val_to_name(dlt_type);
    if (tstamp_name != NULL) {
        printf("Timestamp Type Name: %s\n", tstamp_name);
    }

    pcap_close(handle);
    return 0;
}