// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_nametoport at nametoaddr.c:304:1 in namedb.h
// pcap_nametoaddr at nametoaddr.c:138:1 in namedb.h
// pcap_nametonetaddr at nametoaddr.c:220:1 in namedb.h
// pcap_nametoaddrinfo at nametoaddr.c:178:1 in namedb.h
// pcap_nametoproto at nametoaddr.c:475:1 in namedb.h
// pcap_nametoeproto at nametoaddr.c:596:1 in namedb.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap/namedb.h>
#include <stdint.h>

static void fuzz_pcap_nametoport(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    
    char *service_name = (char *)malloc(Size + 1);
    if (!service_name) return;
    
    memcpy(service_name, Data, Size);
    service_name[Size] = '\0';
    
    int tcp_port = 0, udp_port = 0;
    pcap_nametoport(service_name, &tcp_port, &udp_port);
    
    free(service_name);
}

static void fuzz_pcap_nametoaddr(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    
    char *hostname = (char *)malloc(Size + 1);
    if (!hostname) return;
    
    memcpy(hostname, Data, Size);
    hostname[Size] = '\0';
    
    pcap_nametoaddr(hostname);
    
    free(hostname);
}

static void fuzz_pcap_nametonetaddr(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    
    char *network_name = (char *)malloc(Size + 1);
    if (!network_name) return;
    
    memcpy(network_name, Data, Size);
    network_name[Size] = '\0';
    
    pcap_nametonetaddr(network_name);
    
    free(network_name);
}

static void fuzz_pcap_nametoaddrinfo(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    
    char *hostname = (char *)malloc(Size + 1);
    if (!hostname) return;
    
    memcpy(hostname, Data, Size);
    hostname[Size] = '\0';
    
    struct addrinfo *result = pcap_nametoaddrinfo(hostname);
    if (result) {
        freeaddrinfo(result);
    }
    
    free(hostname);
}

static void fuzz_pcap_nametoproto(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    
    char *proto_name = (char *)malloc(Size + 1);
    if (!proto_name) return;
    
    memcpy(proto_name, Data, Size);
    proto_name[Size] = '\0';
    
    pcap_nametoproto(proto_name);
    
    free(proto_name);
}

static void fuzz_pcap_nametoeproto(const uint8_t *Data, size_t Size) {
    if (Size < 1) return;
    
    char *proto_name = (char *)malloc(Size + 1);
    if (!proto_name) return;
    
    memcpy(proto_name, Data, Size);
    proto_name[Size] = '\0';
    
    pcap_nametoeproto(proto_name);
    
    free(proto_name);
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    fuzz_pcap_nametoport(Data, Size);
    fuzz_pcap_nametoaddr(Data, Size);
    fuzz_pcap_nametonetaddr(Data, Size);
    fuzz_pcap_nametoaddrinfo(Data, Size);
    fuzz_pcap_nametoproto(Data, Size);
    fuzz_pcap_nametoeproto(Data, Size);
    return 0;
}