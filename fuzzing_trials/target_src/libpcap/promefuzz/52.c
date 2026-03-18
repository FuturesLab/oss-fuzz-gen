// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_live at pcap.c:2813:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_lookupnet at pcap.c:1547:1 in pcap.h
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_findalldevs at pcap.c:672:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define ERRBUF_SIZE PCAP_ERRBUF_SIZE

static void fuzz_pcap_open_live(const char *device, int snaplen, int promisc, int timeout, char *errbuf) {
    pcap_t *handle = pcap_open_live(device, snaplen, promisc, timeout, errbuf);
    if (handle) {
        pcap_close(handle);
    }
}

static void fuzz_pcap_lookupnet(const char *device, char *errbuf) {
    bpf_u_int32 net, mask;
    pcap_lookupnet(device, &net, &mask, errbuf);
}

static void fuzz_pcap_create(const char *device, char *errbuf) {
    pcap_t *handle = pcap_create(device, errbuf);
    if (handle) {
        pcap_close(handle);
    }
}

static void fuzz_pcap_findalldevs(char *errbuf) {
    pcap_if_t *alldevs;
    if (pcap_findalldevs(&alldevs, errbuf) == 0) {
        pcap_freealldevs(alldevs);
    }
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    char errbuf[ERRBUF_SIZE];
    errbuf[0] = '\0';

    // Ensure the input data is a null-terminated string for device names
    char *device = (char *)malloc(Size + 1);
    if (!device) {
        return 0;
    }
    memcpy(device, Data, Size);
    device[Size] = '\0';

    // Fuzz pcap_open_live
    fuzz_pcap_open_live(device, 65535, 1, 1000, errbuf);

    // Fuzz pcap_lookupnet
    fuzz_pcap_lookupnet(device, errbuf);

    // Fuzz pcap_create
    fuzz_pcap_create(device, errbuf);

    // Fuzz pcap_findalldevs
    fuzz_pcap_findalldevs(errbuf);

    free(device);
    return 0;
}