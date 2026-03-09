// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_snapshot at pcap.c:3520:1 in pcap.h
// pcap_datalink_ext at pcap.c:3010:1 in pcap.h
// pcap_major_version at pcap.c:3536:1 in pcap.h
// pcap_bufsize at pcap.c:3552:1 in pcap.h
// pcap_minor_version at pcap.c:3544:1 in pcap.h
// pcap_is_swapped at pcap.c:3528:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

static pcap_t *initialize_pcap(const char *filename) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(filename, errbuf);
    if (!handle) {
        fprintf(stderr, "Failed to open pcap file: %s\n", errbuf);
    }
    return handle;
}

static void activate_pcap(pcap_t *handle) {
    // Since we don't have access to the internal structure of pcap_t,
    // we will assume that the handle is activated when opened.
    // Normally, activation is done with pcap_activate() for live captures,
    // but for offline captures, the handle is considered activated.
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    // Prepare dummy file with input data
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Initialize pcap handle
    pcap_t *handle = initialize_pcap("./dummy_file");
    if (!handle) return 0;

    // Activate the handle
    activate_pcap(handle);

    // Fuzz target API functions
    int snapshot = pcap_snapshot(handle);
    int datalink_ext = pcap_datalink_ext(handle);
    int major_version = pcap_major_version(handle);
    int bufsize = pcap_bufsize(handle);
    int minor_version = pcap_minor_version(handle);
    int is_swapped = pcap_is_swapped(handle);

    // Print results to suppress unused variable warnings
    printf("snapshot: %d\n", snapshot);
    printf("datalink_ext: %d\n", datalink_ext);
    printf("major_version: %d\n", major_version);
    printf("bufsize: %d\n", bufsize);
    printf("minor_version: %d\n", minor_version);
    printf("is_swapped: %d\n", is_swapped);

    // Cleanup
    pcap_close(handle);

    return 0;
}