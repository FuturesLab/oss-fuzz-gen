#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "pcap/pcap.h"
#include "unistd.h"

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
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