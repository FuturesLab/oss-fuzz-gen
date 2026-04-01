// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_live at pcap.c:2813:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_get_selectable_fd at pcap.c:3595:1 in pcap.h
// pcap_fileno at pcap.c:3587:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_inject at pcap.c:4225:1 in pcap.h
// pcap_stats at pcap.c:3913:1 in pcap.h
// pcap_datalink at pcap.c:3002:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>

static pcap_t* initialize_pcap_handle() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live("any", BUFSIZ, 1, 1000, errbuf);
    return handle;
}

static void cleanup_pcap_handle(pcap_t *handle) {
    if (handle) {
        pcap_close(handle);
    }
}

static void fuzz_pcap_get_selectable_fd(pcap_t *handle) {
    int fd = pcap_get_selectable_fd(handle);
    if (fd != -1) {
        // Perform a simple non-blocking select on the fd
        fd_set readfds;
        struct timeval timeout = { .tv_sec = 0, .tv_usec = 0 };
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        select(fd + 1, &readfds, NULL, NULL, &timeout);
    }
}

static void fuzz_pcap_fileno(pcap_t *handle) {
    int fd = pcap_fileno(handle);
    if (fd != -1) {
        // Perform a simple non-blocking select on the fd
        fd_set readfds;
        struct timeval timeout = { .tv_sec = 0, .tv_usec = 0 };
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        select(fd + 1, &readfds, NULL, NULL, &timeout);
    }
}

static void fuzz_pcap_setfilter(pcap_t *handle) {
    struct bpf_program fp;
    const char filter_exp[] = "tcp";
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == 0) {
        pcap_setfilter(handle, &fp);
        pcap_freecode(&fp);
    }
}

static void fuzz_pcap_inject(pcap_t *handle, const uint8_t *data, size_t size) {
    if (size > 0 && size <= INT_MAX) {
        pcap_inject(handle, data, size);
    }
}

static void fuzz_pcap_stats(pcap_t *handle) {
    struct pcap_stat stats;
    pcap_stats(handle, &stats);
}

static void fuzz_pcap_datalink(pcap_t *handle) {
    pcap_datalink(handle);
}

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    pcap_t *handle = initialize_pcap_handle();
    if (!handle) {
        return 0;
    }

    fuzz_pcap_get_selectable_fd(handle);
    fuzz_pcap_fileno(handle);
    fuzz_pcap_setfilter(handle);
    fuzz_pcap_inject(handle, Data, Size);
    fuzz_pcap_stats(handle);
    fuzz_pcap_datalink(handle);

    cleanup_pcap_handle(handle);
    return 0;
}