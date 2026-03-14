#include <stdint.h>
#include "stdlib.h"
#include "unistd.h"
#include "pcap/pcap.h"
#include "stdio.h"

int LLVMFuzzerTestOneInput_73(const uint8_t *data, size_t size) {
    pcap_t *pcap_handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Create a temporary file to store the input data
    char filename[] = "/tmp/fuzz_pcap_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the pcap file
    pcap_handle = pcap_open_offline(filename, errbuf);
    if (pcap_handle == NULL) {
        // Cleanup the temporary file
        remove(filename);
        return 0;
    }

    // Call the function-under-test
    int minor_version = pcap_minor_version(pcap_handle);

    // Cleanup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_minor_version to pcap_dump_open
    char* ret_pcap_lookupdev_vrojc = pcap_lookupdev(errbuf);
    if (ret_pcap_lookupdev_vrojc == NULL){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function pcap_dump_open with pcap_dump_open_append

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_lookupdev to pcap_setnonblock
    int ret_pcap_snapshot_lzefi = pcap_snapshot(pcap_handle);
    if (ret_pcap_snapshot_lzefi < 0){
    	return 0;
    }

    int ret_pcap_setnonblock_vxwap = pcap_setnonblock(pcap_handle, 0, errbuf);
    if (ret_pcap_setnonblock_vxwap < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    pcap_dumper_t* ret_pcap_dump_open_rhnzb = pcap_dump_open_append(pcap_handle, ret_pcap_lookupdev_vrojc);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_pcap_dump_open_rhnzb == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from pcap_dump_open_append to pcap_perror
    char* ret_pcap_lookupdev_dmden = pcap_lookupdev(errbuf);
    if (ret_pcap_lookupdev_dmden == NULL){
    	return 0;
    }

    pcap_perror(pcap_handle, ret_pcap_lookupdev_dmden);

    // End mutation: Producer.APPEND_MUTATOR

    pcap_close(pcap_handle);
    remove(filename);

    return 0;
}