// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_snapshot at pcap.c:3520:1 in pcap.h
// pcap_major_version at pcap.c:3536:1 in pcap.h
// pcap_minor_version at pcap.c:3544:1 in pcap.h
// pcap_datalink_ext at pcap.c:3010:1 in pcap.h
// pcap_bufsize at pcap.c:3552:1 in pcap.h
// pcap_is_swapped at pcap.c:3528:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to dummy file
    write_dummy_file(Data, Size);

    // Initialize error buffer
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a pcap handle using a dummy file
    pcap_t *handle = pcap_open_offline("./dummy_file", errbuf);
    if (!handle) return 0;

    // Activate the handle if necessary (for offline files it is already activated)
    // pcap_activate(handle); // Not needed for offline files

    // Invoke target functions
    int snapshot_len = pcap_snapshot(handle);
    int major_version = pcap_major_version(handle);
    int minor_version = pcap_minor_version(handle);
    int datalink_ext = pcap_datalink_ext(handle);
    int bufsize = pcap_bufsize(handle);
    int is_swapped = pcap_is_swapped(handle);

    // Print results for debugging purposes (optional)
    printf("Snapshot Length: %d\n", snapshot_len);
    printf("Major Version: %d\n", major_version);
    printf("Minor Version: %d\n", minor_version);
    printf("Datalink Ext: %d\n", datalink_ext);
    printf("Buffer Size: %d\n", bufsize);
    printf("Is Swapped: %d\n", is_swapped);

    // Cleanup
    pcap_close(handle);

    return 0;
}