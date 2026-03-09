#include <stdint.h>
#include <stddef.h>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "pcap/pcap.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define ERRBUF_SIZE 256

static pcap_t *initialize_pcap_handle() {
    char errbuf[ERRBUF_SIZE];
    pcap_t *handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (!handle) {
        fprintf(stderr, "Failed to open dead pcap handle: %s\n", errbuf);
    }
    return handle;
}

static void cleanup_pcap_handle(pcap_t *handle) {
    if (handle) {
        pcap_close(handle);
    }
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    char errbuf[ERRBUF_SIZE];
    pcap_t *handle = initialize_pcap_handle();
    if (!handle) {
        return 0;
    }

    // Fuzz pcap_list_datalinks
    int *dlt_buf = NULL;
    int dlt_count = pcap_list_datalinks(handle, &dlt_buf);
    if (dlt_count >= 0) {
        // Fuzz pcap_set_datalink only if dlt_buf is valid
        if (dlt_count > 0) {
            int random_dlt = dlt_buf[0];

            // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function pcap_set_datalink with pcap_set_buffer_size
            pcap_set_buffer_size(handle, random_dlt);
            // End mutation: Producer.REPLACE_FUNC_MUTATOR


        }
        pcap_free_datalinks(dlt_buf);
    }

    // Fuzz pcap_init
    unsigned int init_opts = 0;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of pcap_init
    int init_result = pcap_init(64, errbuf);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Fuzz pcap_setfilter
    struct bpf_program fp;
    if (Size > 0) {
        // Ensure null-termination of the data used as a string
        char *null_terminated_data = (char *)malloc(Size + 1);
        if (null_terminated_data) {
            memcpy(null_terminated_data, Data, Size);
            null_terminated_data[Size] = '\0';


            // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of pcap_compile_nopcap
            if (pcap_compile_nopcap(65535, Size, &fp, null_terminated_data, 0, PCAP_NETMASK_UNKNOWN) == 0) {
            // End mutation: Producer.REPLACE_ARG_MUTATOR


                pcap_setfilter(handle, &fp);

                // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_setfilter to pcap_perror

                // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_setfilter to pcap_set_tstamp_precision
                int ret_pcap_datalink_name_to_val_acoki = pcap_datalink_name_to_val((const char *)Data);
                if (ret_pcap_datalink_name_to_val_acoki < 0){
                	return 0;
                }

                int ret_pcap_set_tstamp_precision_ntfzq = pcap_set_tstamp_precision(handle, ret_pcap_datalink_name_to_val_acoki);
                if (ret_pcap_set_tstamp_precision_ntfzq < 0){
                	return 0;
                }

                // End mutation: Producer.APPEND_MUTATOR

                char* ret_pcap_lookupdev_brpsg = pcap_lookupdev(errbuf);
                if (ret_pcap_lookupdev_brpsg == NULL){
                	return 0;
                }

                pcap_perror(handle, ret_pcap_lookupdev_brpsg);

                // End mutation: Producer.APPEND_MUTATOR

                pcap_freecode(&fp);
            }

            free(null_terminated_data);
        }
    }


                // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_freecode to pcap_setfilter
                int ret_pcap_major_version_qkrpm = pcap_major_version(handle);
                if (ret_pcap_major_version_qkrpm < 0){
                	return 0;
                }

                int ret_pcap_setfilter_jqydn = pcap_setfilter(handle, &fp);
                if (ret_pcap_setfilter_jqydn < 0){
                	return 0;
                }

                // End mutation: Producer.APPEND_MUTATOR

    cleanup_pcap_handle(handle);
    return 0;
}