// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_set_immediate_mode at pcap.c:2680:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_statustostr at pcap.c:3719:1 in pcap.h
// pcap_set_timeout at pcap.c:2626:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_statustostr at pcap.c:3719:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
// pcap_statustostr at pcap.c:3719:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static pcap_t *initialize_pcap_handle() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create("any", errbuf);
    if (!handle) {
        fprintf(stderr, "Error creating pcap handle: %s\n", errbuf);
        return NULL;
    }
    return handle;
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 3) {
        return 0;
    }

    pcap_t *handle = initialize_pcap_handle();
    if (!handle) {
        return 0;
    }

    int immediate_mode = *(int *)Data;
    int timeout = *(int *)(Data + sizeof(int));
    int activation_status;
    const char *status_str;

    // Set immediate mode
    if (pcap_set_immediate_mode(handle, immediate_mode) != 0) {
        pcap_close(handle);
        return 0;
    }

    // Convert status to string
    status_str = pcap_statustostr(immediate_mode);
    if (status_str) {
        printf("Immediate mode status: %s\n", status_str);
    }

    // Set timeout
    if (pcap_set_timeout(handle, timeout) != 0) {
        pcap_close(handle);
        return 0;
    }

    // Convert status to string
    status_str = pcap_statustostr(timeout);
    if (status_str) {
        printf("Timeout status: %s\n", status_str);
    }

    // Activate the handle
    activation_status = pcap_activate(handle);

    // Convert activation status to string
    status_str = pcap_statustostr(activation_status);
    if (status_str) {
        printf("Activation status: %s\n", status_str);
    }

    // Get error message if activation failed
    if (activation_status != 0) {
        char *err_msg = pcap_geterr(handle);
        if (err_msg) {
            printf("Error: %s\n", err_msg);
        }
    }

    pcap_close(handle);
    return 0;
}