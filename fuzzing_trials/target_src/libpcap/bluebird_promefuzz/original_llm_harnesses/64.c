// This fuzz driver is generated for library libpcap, aiming to fuzz the following functions:
// pcap_init at pcap.c:223:1 in pcap.h
// pcap_open_offline at savefile.c:388:1 in pcap.h
// pcap_list_datalinks at pcap.c:3018:1 in pcap.h
// pcap_free_datalinks at pcap.c:3062:1 in pcap.h
// pcap_compile_nopcap at gencode.c:1351:1 in pcap.h
// pcap_setfilter at pcap.c:3872:1 in pcap.h
// pcap_freecode at gencode.c:1371:1 in pcap.h
// pcap_set_datalink at pcap.c:3068:1 in pcap.h
// pcap_close at pcap.c:4247:1 in pcap.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

static int create_dummy_file(const uint8_t *Data, size_t Size) {
    int fd = open("./dummy_file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) return -1;
    if (write(fd, Data, Size) != Size) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *pcap_handle = NULL;
    int *datalinks = NULL;
    struct bpf_program bpf_prog;
    memset(&bpf_prog, 0, sizeof(bpf_prog));

    // Initialize pcap
    if (pcap_init(PCAP_CHAR_ENC_LOCAL, errbuf) != 0) {
        return 0;
    }

    // Create a dummy file for pcap_open_offline
    if (create_dummy_file(Data, Size) != 0) {
        return 0;
    }

    // Open the dummy file
    pcap_handle = pcap_open_offline("./dummy_file", errbuf);
    if (!pcap_handle) {
        return 0;
    }

    // Test pcap_list_datalinks
    if (pcap_list_datalinks(pcap_handle, &datalinks) >= 0) {
        pcap_free_datalinks(datalinks);
    }

    // Test pcap_compile_nopcap
    if (pcap_compile_nopcap(65535, DLT_EN10MB, &bpf_prog, "tcp", 0, 0) == 0) {
        // Test pcap_setfilter
        pcap_setfilter(pcap_handle, &bpf_prog);
        pcap_freecode(&bpf_prog);
    }

    // Test pcap_set_datalink
    if (datalinks) {
        pcap_set_datalink(pcap_handle, datalinks[0]);
    }

    pcap_close(pcap_handle);
    return 0;
}