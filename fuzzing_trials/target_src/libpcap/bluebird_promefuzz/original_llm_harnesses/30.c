// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_list_datalinks at pcap.c:3018:1 in pcap.h
// pcap_free_datalinks at pcap.c:3062:1 in pcap.h
// pcap_init at pcap.c:223:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_list_datalinks at pcap.c:3018:1 in pcap.h
// pcap_set_datalink at pcap.c:3068:1 in pcap.h
// pcap_free_datalinks at pcap.c:3062:1 in pcap.h
// pcap_compile_nopcap at gencode.c:1351:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void fuzz_pcap_free_datalinks(pcap_t *handle) {
    int *dlt_buf = NULL;
    int dlt_count = pcap_list_datalinks(handle, &dlt_buf);
    if (dlt_count >= 0) {
        pcap_free_datalinks(dlt_buf);
    }
}

static void fuzz_pcap_init() {
    char errbuf[PCAP_ERRBUF_SIZE];
    unsigned int opts = 0; // default options
    pcap_init(opts, errbuf);
}

static void fuzz_pcap_setfilter(pcap_t *handle) {
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, "tcp", 0, PCAP_NETMASK_UNKNOWN) == 0) {
        pcap_setfilter(handle, &fp);
        pcap_freecode(&fp);
    }
}

static void fuzz_pcap_set_datalink(pcap_t *handle) {
    int *dlt_buf = NULL;
    int dlt_count = pcap_list_datalinks(handle, &dlt_buf);
    if (dlt_count > 0) {
        pcap_set_datalink(handle, dlt_buf[0]);
        pcap_free_datalinks(dlt_buf);
    }
}

static void fuzz_pcap_compile_nopcap() {
    struct bpf_program fp;
    int snaplen = 65535;
    int linktype = DLT_EN10MB;
    const char *filter = "ip";
    pcap_compile_nopcap(snaplen, linktype, &fp, filter, 0, PCAP_NETMASK_UNKNOWN);
    pcap_freecode(&fp);
}

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    // Create a dummy file for pcap_open_offline
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) return 0;
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    handle = pcap_open_offline("./dummy_file", errbuf);
    if (!handle) return 0;

    fuzz_pcap_free_datalinks(handle);
    fuzz_pcap_init();
    fuzz_pcap_setfilter(handle);
    fuzz_pcap_set_datalink(handle);
    fuzz_pcap_compile_nopcap();

    pcap_close(handle);
    unlink("./dummy_file");

    return 0;
}