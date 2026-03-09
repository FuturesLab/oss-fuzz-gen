// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_ether_aton at nametoaddr.c:1157:1 in namedb.h
// pcap_nametonetaddr at nametoaddr.c:220:1 in namedb.h
// pcap_lookupnet at pcap.c:1547:1 in pcap.h
// pcap_open_live at pcap.c:2813:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_ether_hostton at nametoaddr.c:1214:1 in namedb.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <namedb.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ERRBUF_SIZE PCAP_ERRBUF_SIZE

static void fuzz_pcap_create(const uint8_t *Data, size_t Size) {
    char errbuf[ERRBUF_SIZE];
    char device[Size + 1];
    memcpy(device, Data, Size);
    device[Size] = '\0'; // Ensure null-terminated string

    pcap_t *handle = pcap_create(device, errbuf);
    if (handle != NULL) {
        pcap_close(handle);
    }
}

static void fuzz_pcap_ether_aton(const uint8_t *Data, size_t Size) {
    char mac_str[Size + 1];
    memcpy(mac_str, Data, Size);
    mac_str[Size] = '\0'; // Ensure null-terminated string

    u_char *mac_addr = pcap_ether_aton(mac_str);
    if (mac_addr != NULL) {
        free(mac_addr);
    }
}

static void fuzz_pcap_nametonetaddr(const uint8_t *Data, size_t Size) {
    char name[Size + 1];
    memcpy(name, Data, Size);
    name[Size] = '\0'; // Ensure null-terminated string

    (void)pcap_nametonetaddr(name);
}

static void fuzz_pcap_lookupnet(const uint8_t *Data, size_t Size) {
    if (Size < 1) return; // Ensure there's at least one byte for device name

    char device[Size + 1];
    memcpy(device, Data, Size);
    device[Size] = '\0'; // Ensure null-terminated string

    bpf_u_int32 net, mask;
    char errbuf[ERRBUF_SIZE];

    (void)pcap_lookupnet(device, &net, &mask, errbuf);
}

static void fuzz_pcap_open_live(const uint8_t *Data, size_t Size) {
    if (Size < 1) return; // Ensure there's at least one byte for device name

    char device[Size + 1];
    memcpy(device, Data, Size);
    device[Size] = '\0'; // Ensure null-terminated string

    char errbuf[ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(device, 65535, 1, 1000, errbuf);
    if (handle != NULL) {
        pcap_close(handle);
    }
}

static void fuzz_pcap_ether_hostton(const uint8_t *Data, size_t Size) {
    char hostname[Size + 1];
    memcpy(hostname, Data, Size);
    hostname[Size] = '\0'; // Ensure null-terminated string

    u_char *eth_addr = pcap_ether_hostton(hostname);
    if (eth_addr != NULL) {
        free(eth_addr);
    }
}

int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    fuzz_pcap_create(Data, Size);
    fuzz_pcap_ether_aton(Data, Size);
    fuzz_pcap_nametonetaddr(Data, Size);
    fuzz_pcap_lookupnet(Data, Size);
    fuzz_pcap_open_live(Data, Size);
    fuzz_pcap_ether_hostton(Data, Size);
    return 0;
}