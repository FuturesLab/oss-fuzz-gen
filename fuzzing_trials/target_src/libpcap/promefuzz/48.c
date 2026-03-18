// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_getnonblock at pcap.c:3620:1 in pcap.h
// pcap_strerror at pcap.c:3786:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_perror at pcap.c:3608:1 in pcap.h
// pcap_statustostr at pcap.c:3719:1 in pcap.h
// pcap_lib_version at pcap-linux.c:6255:1 in pcap.h
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

static pcap_t* create_dummy_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!handle) {
        fprintf(stderr, "Failed to create dummy pcap handle: %s\n", errbuf);
    }
    return handle;
}

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Not enough data to proceed

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = create_dummy_pcap();
    if (!handle) return 0;

    // Fuzz pcap_getnonblock
    int nonblock_state = pcap_getnonblock(handle, errbuf);
    if (nonblock_state == PCAP_ERROR_NOT_ACTIVATED || nonblock_state == PCAP_ERROR) {
        fprintf(stderr, "pcap_getnonblock error: %s\n", errbuf);
    }

    // Fuzz pcap_strerror
    const char *strerror_msg = pcap_strerror(Data[0]);
    if (strerror_msg) {
        printf("pcap_strerror: %s\n", strerror_msg);
    }

    // Fuzz pcap_geterr
    char *geterr_msg = pcap_geterr(handle);
    if (geterr_msg) {
        printf("pcap_geterr: %s\n", geterr_msg);
    }

    // Fuzz pcap_perror
    pcap_perror(handle, "Fuzz pcap_perror");

    // Fuzz pcap_statustostr
    const char *statustostr_msg = pcap_statustostr(Data[0]);
    if (statustostr_msg) {
        printf("pcap_statustostr: %s\n", statustostr_msg);
    }

    // Fuzz pcap_lib_version
    const char *lib_version = pcap_lib_version();
    if (lib_version) {
        printf("pcap_lib_version: %s\n", lib_version);
    }

    pcap_close(handle);
    return 0;
}