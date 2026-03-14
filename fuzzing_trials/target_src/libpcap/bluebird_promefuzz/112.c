#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "pcap/pcap.h"
#include <stdint.h>
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

static pcap_t *initialize_pcap_handle() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_create("any", errbuf);
    if (handle) {
        if (pcap_set_snaplen(handle, 65535) == 0 &&
            pcap_set_promisc(handle, 1) == 0 &&
            pcap_set_timeout(handle, 1000) == 0) {
            return handle;
        }
        pcap_close(handle);
    }
    return NULL;
}

static void cleanup_pcap_handle(pcap_t *handle) {
    if (handle) {
        pcap_close(handle);
    }
}

int LLVMFuzzerTestOneInput_112(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    pcap_t *handle = initialize_pcap_handle();
    if (!handle) return 0;

    int *dlt_buf = NULL;
    int result = pcap_list_datalinks(handle, &dlt_buf);
    if (result >= 0 && dlt_buf) {
        for (int i = 0; i < result; ++i) {
            int dlt = dlt_buf[i];
            pcap_set_datalink(handle, dlt);
        }
        pcap_free_datalinks(dlt_buf);
    }

    int dl_type = pcap_datalink(handle);

    result = pcap_activate(handle);
    if (result >= 0) {
        int new_dlt = *((int *)Data) % 256; // Modulo to keep within a reasonable range
        pcap_set_datalink(handle, new_dlt);
    }

    cleanup_pcap_handle(handle);
    return 0;
}