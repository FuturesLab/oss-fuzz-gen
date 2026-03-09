// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_set_tstamp_type at pcap.c:2635:1 in pcap.h
// pcap_set_tstamp_precision at pcap.c:2704:1 in pcap.h
// pcap_can_set_rfmon at pcap.c:466:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
// pcap_set_datalink at pcap.c:3068:1 in pcap.h
// pcap_setdirection at pcap.c:3884:1 in pcap.h
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

static void cleanup(pcap_t *handle) {
    if (handle) {
        pcap_close(handle);
    }
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 3) {
        return 0;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create("dummy_device", errbuf);
    if (!handle) {
        return 0;
    }

    int tstamp_type = *((int *)Data);
    int tstamp_precision = *((int *)(Data + sizeof(int)));
    int datalink_type = *((int *)(Data + 2 * sizeof(int)));
    Data += 3 * sizeof(int);
    Size -= 3 * sizeof(int);

    // Set timestamp type
    pcap_set_tstamp_type(handle, tstamp_type);

    // Set timestamp precision
    pcap_set_tstamp_precision(handle, tstamp_precision);

    // Check if RF monitor can be set
    pcap_can_set_rfmon(handle);

    // Activate the pcap handle
    if (pcap_activate(handle) != 0) {
        cleanup(handle);
        return 0;
    }

    // Set datalink type
    pcap_set_datalink(handle, datalink_type);

    // Set packet capture direction
    if (Size >= sizeof(pcap_direction_t)) {
        pcap_direction_t direction = *((pcap_direction_t *)Data);
        pcap_setdirection(handle, direction);
    }

    cleanup(handle);
    return 0;
}