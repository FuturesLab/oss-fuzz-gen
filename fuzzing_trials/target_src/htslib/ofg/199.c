#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hfile.h" // Include the necessary header for hFILE and hdopen

int LLVMFuzzerTestOneInput_199(const uint8_t *data, size_t size) {
    int fd;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    char *mode = "r"; // Default mode

    // Create a temporary file and write the fuzz data into it
    fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // If file creation fails, exit
    }

    // Write the fuzz data to the file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0; // If writing fails, clean up and exit
    }

    // Reopen the file descriptor as hdopen will open it
    fd = open(tmpl, O_RDONLY);
    if (fd == -1) {
        unlink(tmpl);
        return 0; // If reopening fails, clean up and exit
    }

    // Call the function-under-test
    hFILE *hfile = hdopen(fd, mode);

    // Clean up
    if (hfile != NULL) {
        hclose(hfile);
    }
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

    LLVMFuzzerTestOneInput_199(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
