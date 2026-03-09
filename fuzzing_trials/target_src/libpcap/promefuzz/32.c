// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_nametoeproto at nametoaddr.c:596:1 in namedb.h
// pcap_nametoport at nametoaddr.c:304:1 in namedb.h
// pcap_nametoportrange at nametoaddr.c:437:1 in namedb.h
// pcap_nametollc at nametoaddr.c:613:1 in namedb.h
// pcap_datalink_name_to_val at pcap.c:3417:1 in pcap.h
// pcap_nametoproto at nametoaddr.c:475:1 in namedb.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <namedb.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

static void fuzz_pcap_nametoeproto(const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        char *name = strndup((const char *)Data, Size);
        if (name) {
            pcap_nametoeproto(name);
            free(name);
        }
    }
}

static void fuzz_pcap_nametoport(const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        char *name = strndup((const char *)Data, Size);
        if (name) {
            int tcp_port = 0, udp_port = 0;
            pcap_nametoport(name, &tcp_port, &udp_port);
            free(name);
        }
    }
}

static void fuzz_pcap_nametoportrange(const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        char *range = strndup((const char *)Data, Size);
        if (range) {
            int first_port = 0, last_port = 0, proto = 0;
            pcap_nametoportrange(range, &first_port, &last_port, &proto);
            free(range);
        }
    }
}

static void fuzz_pcap_nametollc(const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        char *name = strndup((const char *)Data, Size);
        if (name) {
            pcap_nametollc(name);
            free(name);
        }
    }
}

static void fuzz_pcap_datalink_name_to_val(const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        char *name = strndup((const char *)Data, Size);
        if (name) {
            pcap_datalink_name_to_val(name);
            free(name);
        }
    }
}

static void fuzz_pcap_nametoproto(const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        char *name = strndup((const char *)Data, Size);
        if (name) {
            pcap_nametoproto(name);
            free(name);
        }
    }
}

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    fuzz_pcap_nametoeproto(Data, Size);
    fuzz_pcap_nametoport(Data, Size);
    fuzz_pcap_nametoportrange(Data, Size);
    fuzz_pcap_nametollc(Data, Size);
    fuzz_pcap_datalink_name_to_val(Data, Size);
    fuzz_pcap_nametoproto(Data, Size);
    return 0;
}