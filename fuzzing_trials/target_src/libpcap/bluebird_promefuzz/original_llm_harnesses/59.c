// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_nametoport at nametoaddr.c:304:1 in namedb.h
// pcap_nametoeproto at nametoaddr.c:596:1 in namedb.h
// pcap_nametoproto at nametoaddr.c:475:1 in namedb.h
// pcap_nametoaddr at nametoaddr.c:138:1 in namedb.h
// pcap_nametonetaddr at nametoaddr.c:220:1 in namedb.h
// pcap_nametoaddrinfo at nametoaddr.c:178:1 in namedb.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "namedb.h"

static void fuzz_pcap_nametoport(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    
    char service_name[256];
    int tcp_port = -1, udp_port = -1;

    size_t copy_size = Size < sizeof(service_name) - 1 ? Size : sizeof(service_name) - 1;
    memcpy(service_name, Data, copy_size);
    service_name[copy_size] = '\0';

    pcap_nametoport(service_name, &tcp_port, &udp_port);
}

static void fuzz_pcap_nametoeproto(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    char proto_name[256];
    size_t copy_size = Size < sizeof(proto_name) - 1 ? Size : sizeof(proto_name) - 1;
    memcpy(proto_name, Data, copy_size);
    proto_name[copy_size] = '\0';

    pcap_nametoeproto(proto_name);
}

static void fuzz_pcap_nametoproto(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    char proto_name[256];
    size_t copy_size = Size < sizeof(proto_name) - 1 ? Size : sizeof(proto_name) - 1;
    memcpy(proto_name, Data, copy_size);
    proto_name[copy_size] = '\0';

    pcap_nametoproto(proto_name);
}

static void fuzz_pcap_nametoaddr(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    char host_name[256];
    size_t copy_size = Size < sizeof(host_name) - 1 ? Size : sizeof(host_name) - 1;
    memcpy(host_name, Data, copy_size);
    host_name[copy_size] = '\0';

    pcap_nametoaddr(host_name);
}

static void fuzz_pcap_nametonetaddr(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    char net_name[256];
    size_t copy_size = Size < sizeof(net_name) - 1 ? Size : sizeof(net_name) - 1;
    memcpy(net_name, Data, copy_size);
    net_name[copy_size] = '\0';

    pcap_nametonetaddr(net_name);
}

static void fuzz_pcap_nametoaddrinfo(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;

    char host_name[256];
    size_t copy_size = Size < sizeof(host_name) - 1 ? Size : sizeof(host_name) - 1;
    memcpy(host_name, Data, copy_size);
    host_name[copy_size] = '\0';

    struct addrinfo *result = pcap_nametoaddrinfo(host_name);
    if (result) {
        freeaddrinfo(result);
    }
}

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    fuzz_pcap_nametoport(Data, Size);
    fuzz_pcap_nametoeproto(Data, Size);
    fuzz_pcap_nametoproto(Data, Size);
    fuzz_pcap_nametoaddr(Data, Size);
    fuzz_pcap_nametonetaddr(Data, Size);
    fuzz_pcap_nametoaddrinfo(Data, Size);
    return 0;
}