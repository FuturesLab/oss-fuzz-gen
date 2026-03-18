// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_set_snaplen at pcap.c:2599:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_set_promisc at pcap.c:2608:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_set_timeout at pcap.c:2626:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
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

static pcap_t* initialize_pcap_handle() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create("dummy_device", errbuf);
    if (handle == NULL) {
        return NULL;
    }
    if (pcap_set_snaplen(handle, 65535) != 0) {
        pcap_close(handle);
        return NULL;
    }
    if (pcap_set_promisc(handle, 1) != 0) {
        pcap_close(handle);
        return NULL;
    }
    if (pcap_set_timeout(handle, 1000) != 0) {
        pcap_close(handle);
        return NULL;
    }
    return handle;
}

static void activate_and_test_pcap(pcap_t *handle) {
    if (pcap_activate(handle) == 0) {
        int *dlt_buf = NULL;
        int num_dlt = pcap_list_datalinks(handle, &dlt_buf);
        if (num_dlt > 0) {
            for (int i = 0; i < num_dlt; ++i) {
                pcap_set_datalink(handle, dlt_buf[i]);
                pcap_datalink(handle);
            }
            pcap_free_datalinks(dlt_buf);
        }

        int *tstamp_types = NULL;
        int num_tstamps = pcap_list_tstamp_types(handle, &tstamp_types);
        if (num_tstamps > 0) {
            pcap_free_tstamp_types(tstamp_types);
        }
    }
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    pcap_t *handle = initialize_pcap_handle();
    if (handle == NULL) return 0;

    activate_and_test_pcap(handle);

    pcap_close(handle);
    return 0;
}