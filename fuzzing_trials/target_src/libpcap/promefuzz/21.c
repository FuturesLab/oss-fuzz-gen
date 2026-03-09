// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_create at pcap.c:2306:1 in pcap.h
// pcap_dump_open at sf-pcap.c:895:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_dump_fopen at sf-pcap.c:981:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1255:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_dump_open_append at sf-pcap.c:998:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1255:1 in pcap.h
// pcap_dump_close at sf-pcap.c:1255:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUMMY_FILE "./dummy_file"
#define ERRBUF_SIZE PCAP_ERRBUF_SIZE

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char errbuf[ERRBUF_SIZE];
    pcap_t *handle = NULL;
    pcap_dumper_t *dumper = NULL;
    struct bpf_program fp;

    // Initialize the error buffer
    memset(errbuf, 0, ERRBUF_SIZE);

    // Ensure the device name is null-terminated
    char *device = (char *)malloc(Size + 1);
    if (!device) return 0;
    memcpy(device, Data, Size);
    device[Size] = '\0';

    // 1. Test pcap_create
    handle = pcap_create(device, errbuf);
    free(device);
    if (handle == NULL) {
        fprintf(stderr, "pcap_create failed: %s\n", errbuf);
        return 0;
    }

    // 2. Test pcap_dump_open
    write_dummy_file(Data, Size);
    dumper = pcap_dump_open(handle, DUMMY_FILE);
    if (dumper == NULL) {
        fprintf(stderr, "pcap_dump_open failed: %s\n", pcap_geterr(handle));
        pcap_close(handle);
        return 0;
    }

    // 3. Test pcap_dump_fopen
    FILE *fp_file = fopen(DUMMY_FILE, "rb");
    if (fp_file) {
        pcap_dumper_t *fopen_dumper = pcap_dump_fopen(handle, fp_file);
        if (fopen_dumper == NULL) {
            fprintf(stderr, "pcap_dump_fopen failed: %s\n", pcap_geterr(handle));
        } else {
            pcap_dump_close(fopen_dumper);
        }
        fclose(fp_file);
    }

    // 4. Test pcap_setfilter
    if (pcap_compile(handle, &fp, "tcp", 0, PCAP_NETMASK_UNKNOWN) == 0) {
        if (pcap_setfilter(handle, &fp) != 0) {
            fprintf(stderr, "pcap_setfilter failed: %s\n", pcap_geterr(handle));
        }
        pcap_freecode(&fp);
    } else {
        fprintf(stderr, "pcap_compile failed: %s\n", pcap_geterr(handle));
    }

    // 5. Test pcap_dump_open_append
    pcap_dumper_t *append_dumper = pcap_dump_open_append(handle, DUMMY_FILE);
    if (append_dumper == NULL) {
        fprintf(stderr, "pcap_dump_open_append failed: %s\n", pcap_geterr(handle));
    } else {
        pcap_dump_close(append_dumper);
    }

    // Cleanup
    pcap_dump_close(dumper);
    pcap_close(handle);

    return 0;
}