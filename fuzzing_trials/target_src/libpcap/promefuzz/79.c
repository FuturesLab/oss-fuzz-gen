// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_set_rfmon at pcap.c:2617:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_setnonblock at pcap.c:3664:1 in pcap.h
// pcap_activate at pcap.c:2759:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_open_live at pcap.c:2813:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <unistd.h>

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create("any", errbuf);
    if (!handle) return 0;

    int rfmon = Data[0] % 2;
    pcap_set_rfmon(handle, rfmon);

    struct bpf_program fp;
    memset(&fp, 0, sizeof(fp));

    char filter_exp[] = "tcp";
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == 0) {
        pcap_setfilter(handle, &fp);
        pcap_freecode(&fp);
    }

    pcap_setnonblock(handle, 1, errbuf);

    int activation_result = pcap_activate(handle);
    if (activation_result >= 0) {
        pcap_close(handle);
    } else {
        pcap_close(handle);
        return 0;
    }

    handle = pcap_open_live("any", 65535, 1, 1000, errbuf);
    if (handle) {
        pcap_close(handle);
    }

    write_dummy_file(Data, Size);
    return 0;
}