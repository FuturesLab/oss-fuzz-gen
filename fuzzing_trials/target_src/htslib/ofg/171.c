#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // Include this for mkstemp, write, close, and unlink
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate an htsFile input
    char tmpl[] = "/tmp/fuzz_htsfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Unable to create temporary file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0; // Failed to write data to the file
    }

    // Close the file descriptor to reopen it with hts_open
    close(fd);

    // Open the temporary file as an htsFile
    htsFile *hts_fp = hts_open(tmpl, "r");
    if (hts_fp == NULL) {
        unlink(tmpl);
        return 0; // Failed to open the file as an htsFile
    }

    // Call the function-under-test
    int result = hts_check_EOF(hts_fp);

    // Clean up
    hts_close(hts_fp);
    unlink(tmpl);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_171(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
