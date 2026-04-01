#include <pcap.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // For close()

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Initialize variables
    pcap_t *pcap_handle = NULL;
    FILE *file = NULL;
    pcap_dumper_t *dumper = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];
    char tmp_filename[] = "tempfileXXXXXX";

    // Create a temporary file
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }
    file = fdopen(fd, "wb+");
    if (file == NULL) {
        close(fd);
        return 0;
    }

    // Write the input data to the temporary file
    if (fwrite(data, 1, size, file) != size) {
        fclose(file);
        remove(tmp_filename);
        return 0;
    }
    rewind(file);

    // Initialize pcap handle with dummy values
    pcap_handle = pcap_open_dead(DLT_EN10MB, 65535);
    if (pcap_handle == NULL) {
        fclose(file);
        remove(tmp_filename);
        return 0;
    }

    // Call the function under test
    dumper = pcap_dump_fopen(pcap_handle, file);

    // Clean up
    if (dumper != NULL) {
        pcap_dump_close(dumper);
    }
    pcap_close(pcap_handle);
    fclose(file);
    remove(tmp_filename);

    return 0;
}