#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>
#include <htslib/hfile.h> // Include for hFILE, hopen, and hclose

int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a meaningful test
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor as hts_open will open it again
    close(fd);

    // Open the file using htslib
    struct hFILE *hfile = hopen(tmpl, "r");
    if (hfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare a format structure
    htsFormat format;
    memset(&format, 0, sizeof(htsFormat));

    // Call the function-under-test
    int result = hts_detect_format2(hfile, tmpl, &format);

    // Clean up
    hclose(hfile);
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

    LLVMFuzzerTestOneInput_205(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
