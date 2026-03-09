// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_tstamp_type_name_to_val at pcap.c:3484:1 in pcap.h
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_list_tstamp_types at pcap.c:492:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_set_tstamp_precision at pcap.c:2704:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_tstamp_type_val_to_description at pcap.c:3508:1 in pcap.h
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_set_tstamp_type at pcap.c:2635:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_tstamp_type_val_to_name at pcap.c:3496:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void fuzz_pcap_tstamp_type_name_to_val(const uint8_t *Data, size_t Size) {
    char *name = malloc(Size + 1);
    if (!name) return;
    memcpy(name, Data, Size);
    name[Size] = '\0';
    pcap_tstamp_type_name_to_val(name);
    free(name);
}

static void fuzz_pcap_list_tstamp_types() {
    pcap_t *handle = pcap_create("dummy_device", NULL);
    if (!handle) return;
    int *tstamp_types;
    pcap_list_tstamp_types(handle, &tstamp_types);
    free(tstamp_types);
    pcap_close(handle);
}

static void fuzz_pcap_set_tstamp_precision() {
    pcap_t *handle = pcap_create("dummy_device", NULL);
    if (!handle) return;
    pcap_set_tstamp_precision(handle, PCAP_TSTAMP_PRECISION_MICRO);
    pcap_close(handle);
}

static void fuzz_pcap_tstamp_type_val_to_description(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int val;
    memcpy(&val, Data, sizeof(int));
    pcap_tstamp_type_val_to_description(val);
}

static void fuzz_pcap_set_tstamp_type(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    pcap_t *handle = pcap_create("dummy_device", NULL);
    if (!handle) return;
    int val;
    memcpy(&val, Data, sizeof(int));
    pcap_set_tstamp_type(handle, val);
    pcap_close(handle);
}

static void fuzz_pcap_tstamp_type_val_to_name(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    int val;
    memcpy(&val, Data, sizeof(int));
    pcap_tstamp_type_val_to_name(val);
}

int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    fuzz_pcap_tstamp_type_name_to_val(Data, Size);
    fuzz_pcap_list_tstamp_types();
    fuzz_pcap_set_tstamp_precision();
    fuzz_pcap_tstamp_type_val_to_description(Data, Size);
    fuzz_pcap_set_tstamp_type(Data, Size);
    fuzz_pcap_tstamp_type_val_to_name(Data, Size);
    return 0;
}