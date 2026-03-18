// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_lib_version at pcap-linux.c:6255:1 in pcap.h
// pcap_findalldevs at pcap.c:672:1 in pcap.h
// pcap_freealldevs at pcap.c:1414:1 in pcap.h
// pcap_open_live at pcap.c:2813:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
// pcap_lookupnet at pcap.c:1547:1 in pcap.h
// pcap_statustostr at pcap.c:3719:1 in pcap.h
// pcap_strerror at pcap.c:3786:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_BUFFER_SIZE 256

static void fuzz_pcap_lib_version() {
    const char *version = pcap_lib_version();
    if (version) {
        printf("Libpcap version: %s\n", version);
    }
}

static void fuzz_pcap_findalldevs() {
    pcap_if_t *alldevs;
    char errbuf[ERROR_BUFFER_SIZE];

    int result = pcap_findalldevs(&alldevs, errbuf);
    if (result == -1) {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        return;
    }

    pcap_if_t *d;
    for (d = alldevs; d != NULL; d = d->next) {
        printf("Device: %s\n", d->name);
        if (d->description) {
            printf("Description: %s\n", d->description);
        }
    }

    pcap_freealldevs(alldevs);
}

static void fuzz_pcap_open_live(const char *device) {
    char errbuf[ERROR_BUFFER_SIZE];
    pcap_t *handle = pcap_open_live(device, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Error in pcap_open_live: %s\n", errbuf);
        return;
    }

    printf("Opened device %s for live capture\n", device);
    pcap_close(handle);
}

static void fuzz_pcap_lookupnet(const char *device) {
    bpf_u_int32 net, mask;
    char errbuf[ERROR_BUFFER_SIZE];

    int result = pcap_lookupnet(device, &net, &mask, errbuf);
    if (result == -1) {
        fprintf(stderr, "Error in pcap_lookupnet: %s\n", errbuf);
        return;
    }

    printf("Device %s: Network: %u, Mask: %u\n", device, net, mask);
}

static void fuzz_pcap_statustostr(int status) {
    const char *status_str = pcap_statustostr(status);
    printf("Status %d: %s\n", status, status_str);
}

static void fuzz_pcap_strerror(int errnum) {
    const char *error_str = pcap_strerror(errnum);
    printf("Error %d: %s\n", errnum, error_str);
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    fuzz_pcap_lib_version();
    fuzz_pcap_findalldevs();

    // Use a portion of the input data as a device name
    char device_name[Size + 1];
    memcpy(device_name, Data, Size);
    device_name[Size] = '\0';

    fuzz_pcap_open_live(device_name);
    fuzz_pcap_lookupnet(device_name);

    // Use the first byte of input data as a status/error code
    int status_code = Data[0];
    fuzz_pcap_statustostr(status_code);
    fuzz_pcap_strerror(status_code);

    return 0;
}