#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "pcap/pcap.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    bpf_u_int32 net = 0, mask = 0;
    struct bpf_program fp;
    pcap_t *handle = NULL;

    // Prepare a dummy file
    write_dummy_file(Data, Size);

    // Explore pcap_statustostr
    int status_code = Data[0];
    const char *status_str = pcap_statustostr(status_code);

    // Explore pcap_geterr
    char *error_msg = pcap_geterr(handle);

    // Re-explore pcap_statustostr
    status_str = pcap_statustostr(status_code);

    // Re-explore pcap_geterr
    error_msg = pcap_geterr(handle);

    // Explore pcap_lookupnet
    int lookup_result = pcap_lookupnet("any", &net, &mask, errbuf);

    // Explore pcap_compile
    handle = pcap_open_offline("./dummy_file", errbuf);
    if (handle) {
        char filter_exp[] = "tcp";
        int optimize = 1;
        if (pcap_compile(handle, &fp, filter_exp, optimize, mask) == 0) {
            // Explore pcap_setfilter
            int setfilter_result = pcap_setfilter(handle, &fp);

            // Explore pcap_geterr
            error_msg = pcap_geterr(handle);

            // Explore pcap_breakloop

            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_geterr to pcap_lookupnet
            char oclsxiei[1024] = "hylpw";


            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_geterr to pcap_setdirection

            int ret_pcap_setdirection_rcchf = pcap_setdirection(handle, 0);
            if (ret_pcap_setdirection_rcchf < 0){
            	return 0;
            }

            // End mutation: Producer.APPEND_MUTATOR

            int ret_pcap_lookupnet_hkigk = pcap_lookupnet(error_msg, NULL, NULL, oclsxiei);
            if (ret_pcap_lookupnet_hkigk < 0){
            	return 0;
            }

            // End mutation: Producer.APPEND_MUTATOR

            pcap_breakloop(handle);

            // Clean up

            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_breakloop to pcap_dump_open_append
            char pnqznlgh[1024] = "wswko";
            char* ret_pcap_lookupdev_pdyfs = pcap_lookupdev(pnqznlgh);
            if (ret_pcap_lookupdev_pdyfs == NULL){
            	return 0;
            }

            pcap_dumper_t* ret_pcap_dump_open_append_bocmb = pcap_dump_open_append(handle, ret_pcap_lookupdev_pdyfs);
            if (ret_pcap_dump_open_append_bocmb == NULL){
            	return 0;
            }

            // End mutation: Producer.APPEND_MUTATOR

            pcap_freecode(&fp);
        }
        pcap_close(handle);
    }   return 0;
}