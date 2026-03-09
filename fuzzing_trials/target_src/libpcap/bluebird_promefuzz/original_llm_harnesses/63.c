// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_list_datalinks at pcap.c:3018:1 in pcap.h
// pcap_set_datalink at pcap.c:3068:1 in pcap.h
// pcap_free_datalinks at pcap.c:3062:1 in pcap.h
// pcap_init at pcap.c:223:1 in pcap.h
// pcap_compile_nopcap at gencode.c:1351:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRBUF_SIZE 256

static pcap_t *initialize_pcap_handle() {
    char errbuf[ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!handle) {
        fprintf(stderr, "Failed to open dead pcap handle: %s\n", errbuf);
    }
    return handle;
}

static void cleanup_pcap_handle(pcap_t *handle) {
    if (handle) {
        pcap_close(handle);
    }
}

int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    char errbuf[ERRBUF_SIZE];
    pcap_t *handle = initialize_pcap_handle();
    if (!handle) {
        return 0;
    }

    // Fuzz pcap_list_datalinks
    int *dlt_buf = NULL;
    int dlt_count = pcap_list_datalinks(handle, &dlt_buf);
    if (dlt_count >= 0) {
        // Fuzz pcap_set_datalink only if dlt_buf is valid
        if (dlt_count > 0) {
            int random_dlt = dlt_buf[0];
            pcap_set_datalink(handle, random_dlt);
        }
        pcap_free_datalinks(dlt_buf);
    }

    // Fuzz pcap_init
    unsigned int init_opts = 0;
    int init_result = pcap_init(init_opts, errbuf);

    // Fuzz pcap_setfilter
    struct bpf_program fp;
    if (Size > 0) {
        // Ensure null-termination of the data used as a string
        char *null_terminated_data = (char *)malloc(Size + 1);
        if (null_terminated_data) {
            memcpy(null_terminated_data, Data, Size);
            null_terminated_data[Size] = '\0';

            if (pcap_compile_nopcap(65535, DLT_EN10MB, &fp, null_terminated_data, 0, PCAP_NETMASK_UNKNOWN) == 0) {
                pcap_setfilter(handle, &fp);
                pcap_freecode(&fp);
            }

            free(null_terminated_data);
        }
    }

    cleanup_pcap_handle(handle);
    return 0;
}