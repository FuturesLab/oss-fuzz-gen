// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_nametoaddr at nametoaddr.c:138:1 in namedb.h
// pcap_nametoeproto at nametoaddr.c:596:1 in namedb.h
// pcap_nametonetaddr at nametoaddr.c:220:1 in namedb.h
// pcap_nametoport at nametoaddr.c:304:1 in namedb.h
// pcap_nametoaddrinfo at nametoaddr.c:178:1 in namedb.h
// pcap_nametoproto at nametoaddr.c:475:1 in namedb.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include "pcap.h"

// Dummy file path
#define DUMMY_FILE "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    // Ensure null-terminated strings
    char *hostname = (char *)malloc(Size + 1);
    if (!hostname) return 0;
    memcpy(hostname, Data, Size);
    hostname[Size] = '\0';

    // pcap_nametoaddr
    (void)pcap_nametoaddr(hostname);

    // pcap_nametoeproto
    (void)pcap_nametoeproto(hostname);

    // pcap_nametonetaddr
    (void)pcap_nametonetaddr(hostname);

    // pcap_nametoport
    int tcp_port, udp_port;
    (void)pcap_nametoport(hostname, &tcp_port, &udp_port);

    // pcap_nametoaddrinfo
    struct addrinfo *addr_info = pcap_nametoaddrinfo(hostname);
    if (addr_info) {
        freeaddrinfo(addr_info);  // Free addr_info to prevent memory leak
    }

    // pcap_nametoproto
    (void)pcap_nametoproto(hostname);

    free(hostname);
    return 0;
}