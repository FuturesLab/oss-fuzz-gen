// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <bpf.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static void write_dummy_file(const char *filename, const uint8_t *Data, size_t Size) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const char *dummy_filename = "./dummy_file";
    write_dummy_file(dummy_filename, Data, Size);

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = pcap_open_offline(dummy_filename, errbuf);
    if (!pcap_handle) return 0;

    struct bpf_program fp;
    char filter_exp[] = "tcp";
    bpf_u_int32 net = 0;

    if (pcap_compile(pcap_handle, &fp, filter_exp, 0, net) == -1) {
        pcap_close(pcap_handle);
        return 0;
    }

    if (pcap_setfilter(pcap_handle, &fp) == -1) {
        pcap_freecode(&fp);
        pcap_close(pcap_handle);
        return 0;
    }

    bpf_dump(&fp, 3);

    struct bpf_insn dummy_insn = {0};
    char *image = bpf_image(&dummy_insn, 1);
    if (image) {
        free(image);
    }

    if (bpf_validate(&dummy_insn, 1)) {
        struct pcap_pkthdr pkthdr;
        const u_char *packet_data = Data;
        pcap_offline_filter(&fp, &pkthdr, packet_data);
    }

    pcap_freecode(&fp);
    pcap_close(pcap_handle);

    return 0;
}