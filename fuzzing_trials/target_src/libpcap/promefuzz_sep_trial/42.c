// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_major_version at pcap.c:3536:1 in pcap.h
// pcap_snapshot at pcap.c:3520:1 in pcap.h
// pcap_minor_version at pcap.c:3544:1 in pcap.h
// pcap_datalink_ext at pcap.c:3010:1 in pcap.h
// pcap_bufsize at pcap.c:3552:1 in pcap.h
// pcap_is_swapped at pcap.c:3528:1 in pcap.h
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

static pcap_t *initialize_pcap_handle() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create("dummy_device", errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Failed to create pcap handle: %s\n", errbuf);
        return NULL;
    }
    if (pcap_activate(handle) != 0) {
        pcap_close(handle);
        return NULL;
    }
    return handle;
}

static void cleanup_pcap_handle(pcap_t *handle) {
    if (handle != NULL) {
        pcap_close(handle);
    }
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    pcap_t *handle = initialize_pcap_handle();
    if (handle == NULL) {
        return 0;
    }

    // Fuzz pcap_major_version
    int major_version = pcap_major_version(handle);

    // Fuzz pcap_snapshot
    int snapshot_length = pcap_snapshot(handle);

    // Fuzz pcap_minor_version
    int minor_version = pcap_minor_version(handle);

    // Fuzz pcap_datalink_ext
    int datalink_ext = pcap_datalink_ext(handle);

    // Fuzz pcap_bufsize
    int bufsize = pcap_bufsize(handle);

    // Fuzz pcap_is_swapped
    int is_swapped = pcap_is_swapped(handle);

    // Use the data to randomly decide if we should print the results
    if (Size > 0 && Data[0] % 2 == 0) {
        printf("Major Version: %d\n", major_version);
        printf("Snapshot Length: %d\n", snapshot_length);
        printf("Minor Version: %d\n", minor_version);
        printf("Datalink Ext: %d\n", datalink_ext);
        printf("Buffer Size: %d\n", bufsize);
        printf("Is Swapped: %d\n", is_swapped);
    }

    cleanup_pcap_handle(handle);
    return 0;
}