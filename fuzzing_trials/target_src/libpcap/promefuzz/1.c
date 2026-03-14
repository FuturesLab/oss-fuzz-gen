// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_strerror at pcap.c:3786:1 in pcap.h
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_datalink_name_to_val at pcap.c:3417:1 in pcap.h
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdio.h>
#include <string.h>

static void write_dummy_file(const char *filename, const uint8_t *Data, size_t Size) {
    FILE *file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    const char *dummy_filename = "./dummy_file";
    write_dummy_file(dummy_filename, Data, Size);

    // Invoke pcap_strerror
    int error_code = (int)Data[0];
    const char *error_message = pcap_strerror(error_code);
    if (error_message == NULL) {
        return 0;
    }

    // Invoke pcap_open_offline
    pcap_t *pcap_handle = pcap_open_offline(dummy_filename, errbuf);
    if (pcap_handle == NULL) {
        return 0;
    }

    // Invoke pcap_datalink_name_to_val
    char dlt_name[16];
    snprintf(dlt_name, sizeof(dlt_name), "DLT_%d", Data[0]);
    int dlt_val = pcap_datalink_name_to_val(dlt_name);

    // Invoke pcap_open_dead
    pcap_t *pcap_dead_handle = pcap_open_dead(dlt_val, 65535);
    if (pcap_dead_handle == NULL) {
        pcap_close(pcap_handle);
        return 0;
    }

    // Prepare for pcap_compile
    struct bpf_program fp;
    const char *filter_exp = "tcp";
    bpf_u_int32 netmask = 0xFFFFFF00;

    // Invoke pcap_compile
    int compile_status = pcap_compile(pcap_dead_handle, &fp, filter_exp, 0, netmask);
    if (compile_status == 0) {
        pcap_freecode(&fp);
    }

    // Cleanup
    pcap_close(pcap_handle);
    pcap_close(pcap_dead_handle);

    return 0;
}