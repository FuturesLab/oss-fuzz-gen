// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
// pcap_major_version at pcap.c:3536:1 in pcap.h
// pcap_minor_version at pcap.c:3544:1 in pcap.h
// pcap_snapshot at pcap.c:3520:1 in pcap.h
// pcap_datalink_ext at pcap.c:3010:1 in pcap.h
// pcap_bufsize at pcap.c:3552:1 in pcap.h
// pcap_is_swapped at pcap.c:3528:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <signal.h>

static pcap_t* initialize_pcap(const char *filename) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(filename, errbuf);
    if (!handle) {
        fprintf(stderr, "Error opening file: %s\n", errbuf);
    }
    return handle;
}

static void cleanup_pcap(pcap_t *handle) {
    if (handle) {
        pcap_close(handle);
    }
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        return 0;
    }

    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    pcap_t *handle = initialize_pcap("./dummy_file");
    if (!handle) {
        return 0;
    }

    // Attempt to activate the pcap handle
    int activate_result = pcap_activate(handle);
    if (activate_result < 0) {
        cleanup_pcap(handle);
        return 0;
    }

    // Fuzz various API functions
    int major_version = pcap_major_version(handle);
    int minor_version = pcap_minor_version(handle);
    int snapshot = pcap_snapshot(handle);
    int datalink_ext = pcap_datalink_ext(handle);
    int bufsize = pcap_bufsize(handle);
    int is_swapped = pcap_is_swapped(handle);

    // Use the return values to avoid compiler optimizations
    if (major_version == PCAP_ERROR_NOT_ACTIVATED || 
        minor_version == PCAP_ERROR_NOT_ACTIVATED || 
        snapshot == PCAP_ERROR_NOT_ACTIVATED || 
        datalink_ext == PCAP_ERROR_NOT_ACTIVATED || 
        bufsize == PCAP_ERROR_NOT_ACTIVATED || 
        is_swapped == PCAP_ERROR_NOT_ACTIVATED) {
        fprintf(stderr, "Error: Not activated\n");
    }

    cleanup_pcap(handle);
    return 0;
}