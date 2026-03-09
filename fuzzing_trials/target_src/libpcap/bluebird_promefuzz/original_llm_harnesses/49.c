// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// bpf_validate at bpf_filter.c:541:1 in bpf.h
// pcap_offline_filter at pcap.c:4359:1 in pcap.h
// bpf_filter at bpf_filter.c:534:1 in bpf.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_compile_nopcap at gencode.c:1351:1 in pcap.h
// bpf_validate at bpf_filter.c:541:1 in bpf.h
// bpf_filter at bpf_filter.c:534:1 in bpf.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <bpf.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) return;
    write(fd, Data, Size);
    close(fd);
}

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy file for pcap_open_dead
    write_dummy_file(Data, Size);

    // Use pcap_open_dead to create a fake pcap_t
    pcap_t *fake_pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!fake_pcap) return 0;

    // Prepare bpf_program and pcap_pkthdr
    struct bpf_program bpf_prog;
    struct pcap_pkthdr pkthdr;
    pkthdr.caplen = Size;
    pkthdr.len = Size;
    memset(&pkthdr.ts, 0, sizeof(pkthdr.ts));

    // Compile a BPF program using pcap_compile
    char filter_exp[] = "tcp";
    if (pcap_compile(fake_pcap, &bpf_prog, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == 0) {
        
        // Validate the BPF program
        if (bpf_validate(bpf_prog.bf_insns, bpf_prog.bf_len)) {
            
            // Apply pcap_offline_filter
            pcap_offline_filter(&bpf_prog, &pkthdr, Data);

            // Apply bpf_filter
            bpf_filter(bpf_prog.bf_insns, Data, pkthdr.len, pkthdr.caplen);
        }
        
        // Free the compiled BPF program
        pcap_freecode(&bpf_prog);
    }

    // Compile using pcap_compile_nopcap
    struct bpf_program bpf_prog_nopcap;
    if (pcap_compile_nopcap(65535, DLT_EN10MB, &bpf_prog_nopcap, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == 0) {
        
        // Validate the BPF program
        if (bpf_validate(bpf_prog_nopcap.bf_insns, bpf_prog_nopcap.bf_len)) {
            
            // Apply bpf_filter
            bpf_filter(bpf_prog_nopcap.bf_insns, Data, pkthdr.len, pkthdr.caplen);
        }
        
        // Free the compiled BPF program
        pcap_freecode(&bpf_prog_nopcap);
    }

    // Cleanup
    pcap_close(fake_pcap);
    return 0;
}