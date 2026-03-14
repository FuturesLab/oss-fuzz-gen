#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "pcap/pcap.h"
#include "stdio.h"
#include <stdint.h>
#include "stdlib.h"
#include "string.h"

static void write_dummy_file() {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return;
    const char dummy_data[] = "dummy data for pcap file";
    fwrite(dummy_data, sizeof(dummy_data) - 1, 1, file);
    fclose(file);
}

static void fuzz_pcap_set_tstamp_precision(pcap_t *pcap, const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int precision = *(int *)Data;
    pcap_set_tstamp_precision(pcap, precision);
}

static void fuzz_pcap_fopen_offline(const uint8_t *Data, size_t Size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    FILE *file = fopen("./dummy_file", "rb");
    if (!file) return;
    pcap_t *pcap = pcap_fopen_offline(file, errbuf);
    if (pcap) {
        pcap_close(pcap);
    }
}

static void fuzz_pcap_open_offline_with_tstamp_precision(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u_int)) return;
    u_int precision = *(u_int *)Data;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_offline_with_tstamp_precision("./dummy_file", precision, errbuf);
    if (pcap) {
        pcap_close(pcap);
    }
}

static void fuzz_pcap_open_dead_with_tstamp_precision(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(int) + sizeof(u_int)) return;
    int linktype = *(int *)Data;
    int snaplen = *(int *)(Data + sizeof(int));
    u_int precision = *(u_int *)(Data + 2 * sizeof(int));
    pcap_t *pcap = pcap_open_dead_with_tstamp_precision(linktype, snaplen, precision);
    if (pcap) {
        pcap_close(pcap);
    }
}

static void fuzz_pcap_get_tstamp_precision(pcap_t *pcap) {
    pcap_get_tstamp_precision(pcap);
}

static void fuzz_pcap_fopen_offline_with_tstamp_precision(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u_int)) return;
    u_int precision = *(u_int *)Data;
    char errbuf[PCAP_ERRBUF_SIZE];
    FILE *file = fopen("./dummy_file", "rb");
    if (!file) return;
    pcap_t *pcap = pcap_fopen_offline_with_tstamp_precision(file, precision, errbuf);
    if (pcap) {
        pcap_close(pcap);
    }
}

int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    write_dummy_file();

    pcap_t *pcap = pcap_open_dead_with_tstamp_precision(DLT_EN10MB, 65535, PCAP_TSTAMP_PRECISION_MICRO);
    if (!pcap) return 0;

    fuzz_pcap_set_tstamp_precision(pcap, Data, Size);
    fuzz_pcap_fopen_offline(Data, Size);
    fuzz_pcap_open_offline_with_tstamp_precision(Data, Size);
    fuzz_pcap_open_dead_with_tstamp_precision(Data, Size);
    fuzz_pcap_get_tstamp_precision(pcap);
    fuzz_pcap_fopen_offline_with_tstamp_precision(Data, Size);

    pcap_close(pcap);
    return 0;
}