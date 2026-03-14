// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <bpf.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

static pcap_t *initialize_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!handle) {
        fprintf(stderr, "Failed to open pcap handle: %s\n", errbuf);
        return NULL;
    }
    return handle;
}

static void cleanup_pcap(pcap_t *handle) {
    if (handle) {
        pcap_close(handle);
    }
}

static struct bpf_program compile_bpf(pcap_t *handle, const char *filter) {
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, filter, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Failed to compile filter: %s\n", pcap_geterr(handle));
        fp.bf_len = 0;
        fp.bf_insns = NULL;
    }
    return fp;
}

static void dump_bpf(const struct bpf_program *prog, int option) {
    if (prog->bf_len > 0 && prog->bf_insns) {
        bpf_dump(prog, option);
    }
}

static void set_bpf_filter(pcap_t *handle, struct bpf_program *prog) {
    if (pcap_setfilter(handle, prog) == -1) {
        fprintf(stderr, "Failed to set filter: %s\n", pcap_geterr(handle));
    }
}

static void validate_bpf(const struct bpf_program *prog) {
    if (prog->bf_len > 0 && prog->bf_insns) {
        if (!bpf_validate(prog->bf_insns, prog->bf_len)) {
            fprintf(stderr, "BPF program is invalid.\n");
        }
    }
}

static void offline_filter_test(const struct bpf_program *prog, const struct pcap_pkthdr *hdr, const u_char *pkt_data) {
    int result = pcap_offline_filter(prog, hdr, pkt_data);
    printf("Offline filter result: %d\n", result);
}

int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize pcap
    pcap_t *handle = initialize_pcap();
    if (!handle) return 0;

    // Prepare filter expression from input data
    char filter_exp[256];
    snprintf(filter_exp, sizeof(filter_exp), "%.*s", (int)Size, Data);

    // Compile BPF program
    struct bpf_program prog = compile_bpf(handle, filter_exp);

    // Dump BPF program
    dump_bpf(&prog, 2);

    // Set BPF filter
    set_bpf_filter(handle, &prog);

    // Validate BPF program
    validate_bpf(&prog);

    // Prepare dummy packet header and data
    struct pcap_pkthdr hdr;
    memset(&hdr, 0, sizeof(hdr));
    u_char pkt_data[256];
    memset(pkt_data, 0, sizeof(pkt_data));

    // Test offline filter
    offline_filter_test(&prog, &hdr, pkt_data);

    // Cleanup
    if (prog.bf_insns) {
        pcap_freecode(&prog);
    }
    cleanup_pcap(handle);

    return 0;
}