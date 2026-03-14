// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_set_rfmon at pcap.c:2617:1 in pcap.h
// pcap_set_timeout at pcap.c:2626:1 in pcap.h
// pcap_set_immediate_mode at pcap.c:2680:1 in pcap.h
// pcap_set_snaplen at pcap.c:2599:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void initialize_pcap_handle(pcap_t **handle, char *errbuf) {
    *handle = pcap_create("any", errbuf);
    if (*handle == NULL) {
        fprintf(stderr, "Error creating pcap handle: %s\n", errbuf);
        exit(EXIT_FAILURE);
    }
}

static void cleanup_pcap_handle(pcap_t *handle) {
    if (handle != NULL) {
        pcap_close(handle);
    }
}

int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 5) {
        return 0;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = NULL;
    initialize_pcap_handle(&handle, errbuf);

    int rfmon = *((int *)Data);
    int timeout = *((int *)(Data + sizeof(int)));
    int immediate = *((int *)(Data + 2 * sizeof(int)));
    int snaplen = *((int *)(Data + 3 * sizeof(int)));
    int activate = *((int *)(Data + 4 * sizeof(int)));

    if (pcap_set_rfmon(handle, rfmon) != 0) {
        fprintf(stderr, "Error setting rfmon mode\n");
    }

    if (pcap_set_timeout(handle, timeout) != 0) {
        fprintf(stderr, "Error setting timeout\n");
    }

    if (pcap_set_immediate_mode(handle, immediate) != 0) {
        fprintf(stderr, "Error setting immediate mode\n");
    }

    if (pcap_set_snaplen(handle, snaplen) != 0) {
        fprintf(stderr, "Error setting snaplen\n");
    }

    if (activate && pcap_activate(handle) != 0) {
        fprintf(stderr, "Error activating pcap handle\n");
    }

    cleanup_pcap_handle(handle);
    return 0;
}