// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// bpf_validate at bpf_filter.c:541:1 in bpf.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
// bpf_filter at bpf_filter.c:534:1 in bpf.h
// pcap_compile_nopcap at gencode.c:1351:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
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

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(struct bpf_insn) + sizeof(struct pcap_pkthdr) + 1) {
        return 0;
    }

    // Prepare a fake pcap_t
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) {
        return 0;
    }

    // Prepare a BPF program
    struct bpf_program fp;
    struct bpf_insn insns[] = {
        {BPF_RET | BPF_K, 0, 0, 0}
    };
    fp.bf_len = 1;
    fp.bf_insns = insns;

    // Prepare packet header and data
    struct pcap_pkthdr pkthdr;
    pkthdr.caplen = Size - sizeof(struct bpf_insn) - sizeof(struct pcap_pkthdr);
    pkthdr.len = pkthdr.caplen;
    const u_char *packet = Data + sizeof(struct bpf_insn) + sizeof(struct pcap_pkthdr);

    // Validate BPF instructions
    if (!bpf_validate(insns, fp.bf_len)) {
        pcap_close(pcap);
        return 0;
    }

    // Compile a BPF filter
    char filter_exp[] = "tcp";
    bpf_u_int32 netmask = 0xFFFFFF00;
    if (pcap_compile(pcap, &fp, filter_exp, 0, netmask) == -1) {
        pcap_close(pcap);
        return 0;
    }

    // Test pcap_offline_filter
    pcap_offline_filter(&fp, &pkthdr, packet);

    // Test bpf_filter
    bpf_filter(insns, packet, pkthdr.len, pkthdr.caplen);

    // Test pcap_compile_nopcap
    struct bpf_program nopcap_fp;
    if (pcap_compile_nopcap(65535, DLT_EN10MB, &nopcap_fp, filter_exp, 0, netmask) == -1) {
        pcap_close(pcap);
        free(fp.bf_insns);
        return 0;
    }

    // Write to a dummy file
    write_dummy_file(Data, Size);

    // Cleanup
    pcap_close(pcap);
    if (fp.bf_insns) {
        free(fp.bf_insns);
    }
    if (nopcap_fp.bf_insns) {
        free(nopcap_fp.bf_insns);
    }

    return 0;
}