// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
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

static void write_dummy_file(const char *filename, const uint8_t *data, size_t size) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) {
        return 0;
    }

    struct bpf_program bpf_prog;
    char filter_exp[256];
    snprintf(filter_exp, sizeof(filter_exp), "tcp port %d", Data[0]);

    int optimize = 1;
    bpf_u_int32 netmask = 0xffffff00;

    if (pcap_compile(pcap, &bpf_prog, filter_exp, optimize, netmask) == 0) {
        int setfilter_result = pcap_setfilter(pcap, &bpf_prog);

        if (setfilter_result == 0) {
            bpf_dump(&bpf_prog, Data[0] % 3);

            if (bpf_prog.bf_insns) {
                bpf_validate(bpf_prog.bf_insns, bpf_prog.bf_len);
                bpf_image(bpf_prog.bf_insns, bpf_prog.bf_len);
            }
        }
        // Free the compiled BPF program to prevent memory leaks
        pcap_freecode(&bpf_prog);
    }

    pcap_close(pcap);

    write_dummy_file("./dummy_file", Data, Size);

    return 0;
}