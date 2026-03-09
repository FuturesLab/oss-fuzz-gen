// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_dump_open at sf-pcap.c:895:1 in pcap.h
// pcap_dump_file at sf-pcap.c:1194:1 in pcap.h
// pcap_dump_ftell at sf-pcap.c:1200:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1255:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>

static pcap_t *initialize_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535);
    if (!pcap) {
        fprintf(stderr, "Failed to initialize pcap: %s\n", errbuf);
    }
    return pcap;
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize pcap
    pcap_t *pcap = initialize_pcap();
    if (!pcap) return 0;

    // Use "./dummy_file" as the filename
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "w+");
    if (!file) {
        pcap_close(pcap);
        return 0;
    }

    // Write Data to the file
    fwrite(Data, 1, Size, file);
    fflush(file);

    // Test pcap_dump_open
    pcap_dumper_t *dumper = pcap_dump_open(pcap, filename);
    if (dumper) {
        // Test pcap_dump_file
        FILE *dumper_file = pcap_dump_file(dumper);
        if (dumper_file) {
            // Avoid using pcap_dump_fopen, as it can cause double-free
            // pcap_dumper_t *dumper_fopen = pcap_dump_fopen(pcap, dumper_file);
            // if (dumper_fopen) {
            //     pcap_dump_close(dumper_fopen);
            // }
        }

        // Test pcap_dump_ftell
        long position = pcap_dump_ftell(dumper);
        (void)position; // Use the position to avoid unused variable warning

        // Close the dumper
        pcap_dump_close(dumper);
    }

    // Test pcap_next_etherent
    rewind(file);
    struct pcap_etherent *etherent;
    while ((etherent = pcap_next_etherent(file)) != NULL) {
        // Process etherent if needed
    }

    // Cleanup
    fclose(file);
    pcap_close(pcap);
    return 0;
}