#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "pcap/pcap.h"
#include <stdint.h>
#include "stdlib.h"
#include "string.h"

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

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
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