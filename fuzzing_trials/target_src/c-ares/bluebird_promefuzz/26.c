#include <stdint.h>
#include "stddef.h"
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ares.h"
#include "/src/c-ares/include/ares_dns_record.h"

static void dummy_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
    // Dummy callback function for ares_search_dnsrec and ares_send_dnsrec
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    ares_channel_t *channel = NULL;
    ares_dns_record_t *dnsrec = NULL;
    unsigned short qid = 0;
    const char *name = NULL;
    ares_dns_rec_type_t qtype;
    ares_dns_class_t qclass;
    ares_dns_rr_t *rr_out;
    ares_dns_section_t sect = 0;
    unsigned int ttl = 0;
    unsigned short id = 0;
    unsigned short flags = 0;
    ares_dns_opcode_t opcode = 0;
    ares_dns_rcode_t rcode = 0;
    size_t idx = 0;

    // Initialize ares channel
    if (ares_init(&channel) != ARES_SUCCESS) {
        return 0;
    }

    // Initialize DNS record
    if (ares_dns_record_create(&dnsrec, id, flags, opcode, rcode) != ARES_SUCCESS) {
        ares_destroy(channel);
        return 0;
    }

    // Fuzz ares_dns_record_query_add
    if (Size > 0) {
        char *name_buf = (char *)malloc(Size + 1);
        if (name_buf) {
            memcpy(name_buf, Data, Size);
            name_buf[Size] = '\0';
            qtype = (ares_dns_rec_type_t)(Data[0] % 256);
            qclass = (ares_dns_class_t)(Data[0] % 256);
            ares_dns_record_query_add(dnsrec, name_buf, qtype, qclass);

            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ares_dns_record_query_add to ares_dns_record_rr_cnt

            size_t ret_ares_dns_record_rr_cnt_mcuyd = ares_dns_record_rr_cnt(dnsrec, 0);
            if (ret_ares_dns_record_rr_cnt_mcuyd < 0){
            	return 0;
            }

            // End mutation: Producer.APPEND_MUTATOR

            free(name_buf);
        }
    }

    // Fuzz ares_dns_record_rr_add
    if (Size > 1) {
        char *name_buf = (char *)malloc(Size + 1);
        if (name_buf) {
            memcpy(name_buf, Data, Size);
            name_buf[Size] = '\0';
            qtype = (ares_dns_rec_type_t)(Data[1] % 256);
            qclass = (ares_dns_class_t)(Data[1] % 256);
            ttl = Data[1];
            ares_dns_record_rr_add(&rr_out, dnsrec, sect, name_buf, qtype, qclass, ttl);
            free(name_buf);
        }
    }

    // Fuzz ares_dns_record_query_get
    if (Size > 2) {
        idx = Data[2] % 256;
        ares_dns_record_query_get(dnsrec, idx, &name, &qtype, &qclass);
    }

    // Fuzz ares_search_dnsrec
    if (Size > 3) {
        ares_search_dnsrec(channel, dnsrec, dummy_callback, NULL);
    }

    // Fuzz ares_send_dnsrec
    if (Size > 4) {
        ares_send_dnsrec(channel, dnsrec, dummy_callback, NULL, &qid);
    }

    // Clean up
    if (dnsrec) {
        ares_dns_record_destroy(dnsrec);
    }
    if (channel) {
        ares_destroy(channel);
    }
    return 0;
}