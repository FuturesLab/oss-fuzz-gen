// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_compile_nopcap at gencode.c:1351:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <bpf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare environment for pcap_compile
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) return 0;

    struct bpf_program fp;
    char filter_exp[256];
    snprintf(filter_exp, sizeof(filter_exp), "%.*s", (int)Size, Data);
    bpf_u_int32 netmask = 0xffffff00;

    // Fuzz pcap_compile
    if (pcap_compile(pcap, &fp, filter_exp, 0, netmask) == 0) {
        // Fuzz bpf_filter
        struct bpf_insn *insns = fp.bf_insns;
        if (insns) {
            u_char packet[1024] = {0};
            bpf_filter(insns, packet, sizeof(packet), sizeof(packet));

            // Fuzz bpf_validate
            bpf_validate(insns, fp.bf_len);

            // Clean up
            pcap_freecode(&fp);
        }
    }

    // Fuzz pcap_compile_nopcap
    struct bpf_program fp_nopcap;
    if (pcap_compile_nopcap(65535, DLT_EN10MB, &fp_nopcap, filter_exp, 0, netmask) == 0) {
        struct bpf_insn *insns_nopcap = fp_nopcap.bf_insns;
        if (insns_nopcap) {
            bpf_filter(insns_nopcap, Data, Size, Size);
            bpf_validate(insns_nopcap, fp_nopcap.bf_len);
            pcap_freecode(&fp_nopcap);
        }
    }

    // Clean up
    pcap_close(pcap);

    // Write data to a dummy file for further fuzzing if needed
    write_dummy_file(Data, Size);

    return 0;
}