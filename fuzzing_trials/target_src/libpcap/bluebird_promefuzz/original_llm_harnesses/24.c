// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_free_datalinks at pcap.c:3062:1 in pcap.h
// pcap_init at pcap.c:223:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_set_datalink at pcap.c:3068:1 in pcap.h
// pcap_list_datalinks at pcap.c:3018:1 in pcap.h
// pcap_compile_nopcap at gencode.c:1351:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void fuzz_pcap_free_datalinks(int *dlt_list) {
    if (dlt_list) {
        pcap_free_datalinks(dlt_list);
    }
}

static void fuzz_pcap_init(unsigned int opts, char *errbuf) {
    pcap_init(opts, errbuf);
}

static void fuzz_pcap_setfilter(pcap_t *p, struct bpf_program *fp) {
    if (p && fp) {
        pcap_setfilter(p, fp);
    }
}

static void fuzz_pcap_set_datalink(pcap_t *p, int dlt) {
    if (p) {
        pcap_set_datalink(p, dlt);
    }
}

static void fuzz_pcap_list_datalinks(pcap_t *p, int **dlt_list) {
    if (p) {
        pcap_list_datalinks(p, dlt_list);
    }
}

static void fuzz_pcap_compile_nopcap(int snaplen, int linktype, struct bpf_program *program, const char *str, int optimize, bpf_u_int32 mask) {
    if (program && str) {
        if (pcap_compile_nopcap(snaplen, linktype, program, str, optimize, mask) == 0) {
            pcap_freecode(program);
        }
    }
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    struct bpf_program fp;
    int *dlt_list = NULL;

    // Fuzzing pcap_init
    fuzz_pcap_init(Data[0], errbuf);

    // Fuzzing pcap_list_datalinks
    fuzz_pcap_list_datalinks(pcap_handle, &dlt_list);

    // Fuzzing pcap_setfilter
    fuzz_pcap_setfilter(pcap_handle, &fp);

    // Fuzzing pcap_set_datalink
    if (dlt_list) {
        fuzz_pcap_set_datalink(pcap_handle, dlt_list[0]);
    }

    // Fuzzing pcap_compile_nopcap
    fuzz_pcap_compile_nopcap(65535, DLT_EN10MB, &fp, "tcp", 1, 0xFFFFFF00);

    // Fuzzing pcap_free_datalinks
    fuzz_pcap_free_datalinks(dlt_list);

    pcap_close(pcap_handle);
    return 0;
}