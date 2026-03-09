// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_statustostr at pcap.c:3719:1 in pcap.h
// pcap_open_live at pcap.c:2813:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_statustostr at pcap.c:3719:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_fileno at pcap.c:3587:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_compile at gencode.c:1186:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_geterr at pcap.c:3614:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void write_dummy_file(const char *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Convert first byte to an error code for pcap_statustostr
    int error_code = Data[0];
    const char *status_str = pcap_statustostr(error_code);

    // Open a live capture session
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live("any", 65535, 1, 1000, errbuf);
    if (!handle) {
        return 0;
    }

    // Get error message from handle
    char *err_msg = pcap_geterr(handle);

    // Reuse pcap_statustostr
    status_str = pcap_statustostr(error_code);

    // Get error message again from handle
    err_msg = pcap_geterr(handle);

    // Retrieve file descriptor
    int fd = pcap_fileno(handle);
    if (fd == PCAP_ERROR) {
        pcap_close(handle);
        return 0;
    }

    // Compile a filter
    struct bpf_program fp;
    if (pcap_compile(handle, &fp, "tcp", 0, PCAP_NETMASK_UNKNOWN) == PCAP_ERROR) {
        err_msg = pcap_geterr(handle);
        pcap_close(handle);
        return 0;
    }

    // Set the filter
    if (pcap_setfilter(handle, &fp) == PCAP_ERROR) {
        err_msg = pcap_geterr(handle);
    }

    // Clean up
    pcap_close(handle);
    return 0;
}