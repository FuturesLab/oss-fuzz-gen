// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_live at pcap.c:2813:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_get_selectable_fd at pcap.c:3595:1 in pcap.h
// pcap_fileno at pcap.c:3587:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_inject at pcap.c:4225:1 in pcap.h
// pcap_stats at pcap.c:3913:1 in pcap.h
// pcap_datalink at pcap.c:3002:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static pcap_t *initialize_pcap_handle() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live("any", BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open device: %s\n", errbuf);
        return NULL;
    }
    return handle;
}

static struct bpf_program compile_filter(pcap_t *handle, const char *filter_exp) {
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Could not parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
    }
    return fp;
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pcap_t *handle = initialize_pcap_handle();
    if (!handle) return 0;

    int selectable_fd = pcap_get_selectable_fd(handle);
    int fileno = pcap_fileno(handle);

    struct bpf_program filter = compile_filter(handle, "tcp");
    pcap_setfilter(handle, &filter);

    const char *packet_data = (const char *)Data;
    size_t packet_size = Size < 65535 ? Size : 65535;
    pcap_inject(handle, packet_data, packet_size);

    struct pcap_stat stats;
    pcap_stats(handle, &stats);

    int link_type = pcap_datalink(handle);

    // Clean up
    pcap_freecode(&filter);
    pcap_close(handle);

    return 0;
}