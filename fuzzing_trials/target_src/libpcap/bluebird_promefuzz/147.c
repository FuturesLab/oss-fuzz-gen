#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "pcap/pcap.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define DUMMY_FILE "./dummy_file"
#define ERRBUF_SIZE PCAP_ERRBUF_SIZE

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Step 1: Prepare environment
    char errbuf[ERRBUF_SIZE];
    int error_code = Data[0]; // Use the first byte as an error code for pcap_strerror
    const char *error_message = pcap_strerror(error_code);

    // Step 2: Invoke pcap_open_offline
    write_dummy_file(Data, Size);
    pcap_t *pcap_offline = pcap_open_offline(DUMMY_FILE, errbuf);
    if (!pcap_offline) {
        return 0; // If failed, return early
    }

    // Step 3: Invoke pcap_datalink_name_to_val
    int dlt_val = pcap_datalink_name_to_val((const char *)Data);

    // Step 4: Invoke pcap_open_dead
    int linktype = dlt_val != -1 ? dlt_val : DLT_EN10MB;
    int snapshot_length = 65535;
    pcap_t *pcap_dead = pcap_open_dead(linktype, snapshot_length);
    if (!pcap_dead) {
        pcap_close(pcap_offline);
        return 0; // If failed, return early
    }

    // Step 5: Invoke pcap_compile
    struct bpf_program fp;
    int optimize = 1;
    bpf_u_int32 netmask = 0xFFFFFF00; // Default netmask

    // Ensure Data is null-terminated before passing to pcap_compile
    char *filter_exp = malloc(Size + 1);
    if (filter_exp) {
        memcpy(filter_exp, Data, Size);
        filter_exp[Size] = '\0';

        // Compile the filter expression

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of pcap_compile
        pcap_compile(pcap_dead, &fp, filter_exp, -1, netmask);
        // End mutation: Producer.REPLACE_ARG_MUTATOR



        // Clean up
        free(filter_exp);
    }

    // Step 6: Cleanup
    pcap_close(pcap_dead);
    pcap_close(pcap_offline);

    return 0;
}