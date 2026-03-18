// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_set_rfmon at pcap.c:2617:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_set_timeout at pcap.c:2626:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_set_snaplen at pcap.c:2599:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_setnonblock at pcap.c:3664:1 in pcap.h
// pcap_open_live at pcap.c:2813:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>

static void setup_pcap_handle(pcap_t *handle) {
    // Attempt to set rfmon mode
    int ret = pcap_set_rfmon(handle, 1);
    if (ret != 0) {
        fprintf(stderr, "Failed to set rfmon: %s\n", pcap_geterr(handle));
    }

    // Attempt to set timeout
    ret = pcap_set_timeout(handle, 1000);
    if (ret != 0) {
        fprintf(stderr, "Failed to set timeout: %s\n", pcap_geterr(handle));
    }

    // Attempt to set snaplen
    ret = pcap_set_snaplen(handle, 65535);
    if (ret != 0) {
        fprintf(stderr, "Failed to set snaplen: %s\n", pcap_geterr(handle));
    }

    // Attempt to set non-blocking mode
    char errbuf[PCAP_ERRBUF_SIZE];
    ret = pcap_setnonblock(handle, 1, errbuf);
    if (ret != 0) {
        fprintf(stderr, "Failed to set nonblock: %s\n", errbuf);
    }
}

int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(NULL, 65535, 1, 1000, errbuf);
    if (!handle) {
        fprintf(stderr, "Failed to open live capture: %s\n", errbuf);
        return 0;
    }

    setup_pcap_handle(handle);

    // Clean up
    pcap_close(handle);
    return 0;
}