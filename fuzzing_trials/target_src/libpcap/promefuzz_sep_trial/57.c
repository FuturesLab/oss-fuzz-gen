// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_lib_version at pcap-linux.c:6255:1 in pcap.h
// pcap_findalldevs at pcap.c:672:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
// pcap_open_live at pcap.c:2813:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_lookupnet at pcap.c:1547:1 in pcap.h
// pcap_statustostr at pcap.c:3719:1 in pcap.h
// pcap_strerror at pcap.c:3786:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void fuzz_pcap_lib_version() {
    const char* version = pcap_lib_version();
    if (version) {
        printf("Libpcap version: %s\n", version);
    }
}

static void fuzz_pcap_findalldevs() {
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];
    if (pcap_findalldevs(&alldevs, errbuf) == 0) {
        pcap_freealldevs(alldevs);
    } else {
        printf("Error in pcap_findalldevs: %s\n", errbuf);
    }
}

static void fuzz_pcap_open_live(const uint8_t *Data, size_t Size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    char devname[256] = "any";
    if (Size > 0) {
        size_t copy_size = (Size < sizeof(devname) - 1) ? Size : sizeof(devname) - 1;
        memcpy(devname, Data, copy_size);
        devname[copy_size] = '\0';
    }
    pcap_t *handle = pcap_open_live(devname, 65535, 1, 1000, errbuf);
    if (handle) {
        pcap_close(handle);
    } else {
        printf("Error in pcap_open_live: %s\n", errbuf);
    }
}

static void fuzz_pcap_lookupnet(const uint8_t *Data, size_t Size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    char devname[256] = "any";
    if (Size > 0) {
        size_t copy_size = (Size < sizeof(devname) - 1) ? Size : sizeof(devname) - 1;
        memcpy(devname, Data, copy_size);
        devname[copy_size] = '\0';
    }
    bpf_u_int32 net, mask;
    if (pcap_lookupnet(devname, &net, &mask, errbuf) == 0) {
        printf("Network: %u, Mask: %u\n", net, mask);
    } else {
        printf("Error in pcap_lookupnet: %s\n", errbuf);
    }
}

static void fuzz_pcap_statustostr() {
    for (int code = -10; code <= 10; ++code) {
        const char* message = pcap_statustostr(code);
        printf("Status %d: %s\n", code, message);
    }
}

static void fuzz_pcap_strerror() {
    for (int err = -10; err <= 10; ++err) {
        const char* message = pcap_strerror(err);
        printf("Error %d: %s\n", err, message);
    }
}

int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    fuzz_pcap_lib_version();
    fuzz_pcap_findalldevs();
    fuzz_pcap_open_live(Data, Size);
    fuzz_pcap_lookupnet(Data, Size);
    fuzz_pcap_statustostr();
    fuzz_pcap_strerror();
    return 0;
}