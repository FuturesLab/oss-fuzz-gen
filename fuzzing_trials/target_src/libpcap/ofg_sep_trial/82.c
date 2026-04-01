#include <stdint.h>
#include <stdio.h>
#include <pcap.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_pcap_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }

    // Write the input data to the temporary file
    if (fwrite(data, 1, size, file) != size) {
        fclose(file);
        remove(filename);
        return 0;
    }
    fclose(file);

    // Re-open the file for reading
    file = fopen(filename, "rb");
    if (file == NULL) {
        remove(filename);
        return 0;
    }

    // Prepare a non-NULL string for the second parameter
    char errbuf[PCAP_ERRBUF_SIZE];
    memset(errbuf, 'A', sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';

    // Call the function-under-test
    pcap_t *pcap_handle = pcap_fopen_offline(file, errbuf);

    // Clean up
    if (pcap_handle != NULL) {
        pcap_close(pcap_handle);
    }
    fclose(file);
    remove(filename);

    return 0;
}