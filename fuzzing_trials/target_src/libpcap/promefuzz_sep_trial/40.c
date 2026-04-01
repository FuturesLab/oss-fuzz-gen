// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
// pcap_fileno at pcap.c:3587:1 in pcap.h
// pcap_inject at pcap.c:4225:1 in pcap.h
// pcap_stats at pcap.c:3913:1 in pcap.h
// pcap_bufsize at pcap.c:3552:1 in pcap.h
// pcap_datalink at pcap.c:3002:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1) {
        write(fd, Data, Size);
        close(fd);
    }
}

static pcap_t* create_and_activate_pcap(const char *device, char *errbuf) {
    pcap_t *handle = pcap_create(device, errbuf);
    if (handle != NULL) {
        pcap_activate(handle);
    }
    return handle;
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    memset(errbuf, 0, sizeof(errbuf));

    // Write dummy file with input data
    write_dummy_file(Data, Size);

    // Create and activate pcap handle
    pcap_t *handle = create_and_activate_pcap("lo", errbuf);
    if (!handle) return 0;

    // Test pcap_fileno
    int fd = pcap_fileno(handle);
    if (fd != PCAP_ERROR) {
        // Test pcap_inject with input data
        pcap_inject(handle, Data, Size < INT_MAX ? Size : INT_MAX - 1);

        // Test pcap_stats
        struct pcap_stat stats;
        pcap_stats(handle, &stats);

        // Test pcap_bufsize
        pcap_bufsize(handle);

        // Test pcap_datalink
        pcap_datalink(handle);
    }

    // Cleanup
    pcap_close(handle);

    return 0;
}