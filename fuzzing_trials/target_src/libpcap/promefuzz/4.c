// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_list_datalinks at pcap.c:3018:1 in pcap.h
// pcap_statustostr at pcap.c:3719:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_datalink_val_to_name at pcap.c:3429:1 in pcap.h
// pcap_free_datalinks at pcap.c:3062:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>

static pcap_t *initialize_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (handle == NULL) {
        fprintf(stderr, "Failed to open pcap handle: %s\n", errbuf);
    }
    return handle;
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    pcap_t *pcap_handle = initialize_pcap();
    if (!pcap_handle) {
        return 0;
    }

    // pcap_geterr
    char *err_msg = pcap_geterr(pcap_handle);

    // pcap_list_datalinks
    int *dlt_buf = NULL;
    int dlt_count = pcap_list_datalinks(pcap_handle, &dlt_buf);
    
    // pcap_statustostr
    int status_code = *((int *)Data);
    const char *status_msg = pcap_statustostr(status_code);

    // pcap_geterr again
    err_msg = pcap_geterr(pcap_handle);

    // pcap_datalink_val_to_name
    const char *dlt_name = NULL;
    if (dlt_count > 0) {
        dlt_name = pcap_datalink_val_to_name(dlt_buf[0]);
    }

    // Cleanup
    if (dlt_buf) {
        pcap_free_datalinks(dlt_buf);
    }
    pcap_close(pcap_handle);

    return 0;
}