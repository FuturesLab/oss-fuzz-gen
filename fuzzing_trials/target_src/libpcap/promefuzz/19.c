// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_open_dead at pcap.c:4620:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_dump_open at sf-pcap.c:895:1 in pcap.h
// pcap_dump_flush at sf-pcap.c:1245:1 in pcap.h
// pcap_dump_file at sf-pcap.c:1194:1 in pcap.h
// pcap_dump_ftell at sf-pcap.c:1200:1 in pcap.h
// pcap_dump_ftell64 at sf-pcap.c:1213:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1255:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

static pcap_t* initialize_pcap() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap = pcap_open_dead(DLT_EN10MB, 65535); // Ethernet and max snapshot length
    if (!pcap) {
        fprintf(stderr, "Failed to create pcap handle: %s\n", errbuf);
    }
    return pcap;
}

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pcap_t *pcap = initialize_pcap();
    if (!pcap) return 0;

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        pcap_close(pcap);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    pcap_dumper_t *dumper = pcap_dump_open(pcap, "./dummy_file");
    if (dumper) {
        pcap_dump_flush(dumper);

        FILE *dumper_file = pcap_dump_file(dumper);
        if (dumper_file) {
            fseek(dumper_file, 0, SEEK_END);
            long file_pos = pcap_dump_ftell(dumper);
            int64_t file_pos_64 = pcap_dump_ftell64(dumper);

            if (file_pos == -1 || file_pos_64 == PCAP_ERROR) {
                fprintf(stderr, "Error in ftell\n");
            }
        }

        pcap_dump_close(dumper);
    } else {
        fprintf(stderr, "Failed to open pcap dumper: %s\n", pcap_geterr(pcap));
    }

    pcap_close(pcap);
    return 0;
}