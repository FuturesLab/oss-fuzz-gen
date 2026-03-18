// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_sendpacket at pcap.c:4207:1 in pcap.h
// pcap_snapshot at pcap.c:3520:1 in pcap.h
// pcap_fileno at pcap.c:3587:1 in pcap.h
// pcap_datalink_ext at pcap.c:3010:1 in pcap.h
// pcap_bufsize at pcap.c:3552:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DUMMY_FILE "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create(DUMMY_FILE, errbuf);
    if (!handle) return 0;

    int activate_status = pcap_activate(handle);
    if (activate_status < 0) {
        pcap_close(handle);
        return 0;
    }

    // Fuzz pcap_sendpacket
    if (Size > 1) {
        pcap_sendpacket(handle, Data, (int)Size);
    }

    // Fuzz pcap_snapshot
    int snapshot_length = pcap_snapshot(handle);

    // Fuzz pcap_fileno
    int fd = pcap_fileno(handle);

    // Fuzz pcap_datalink_ext
    int link_type_ext = pcap_datalink_ext(handle);

    // Fuzz pcap_bufsize
    int buffer_size = pcap_bufsize(handle);

    // Cleanup
    pcap_close(handle);

    return 0;
}