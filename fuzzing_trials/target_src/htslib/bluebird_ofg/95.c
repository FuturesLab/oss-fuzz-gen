#include <sys/stat.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For close, unlink
#include <fcntl.h>  // For mkstemp
#include "htslib/hfile.h" // Correct path for hfile.h

// Remove the 'extern "C"' linkage specification as it is not needed in C
int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to extract meaningful values
    if (size < sizeof(off_t) + sizeof(int)) {
        return 0;
    }

    // Create a temporary file to work with hFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Open the temporary file as an hFILE
    hFILE *hfile = hopen(tmpl, "rb");
    if (hfile == NULL) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Extract an off_t value from the data
    off_t offset = *((off_t *)data);

    // Extract an int value from the data
    int whence = *((int *)(data + sizeof(off_t)));

    // Call the function-under-test
    off_t result = hseek(hfile, offset, whence);

    // Clean up
    hclose(hfile);
    close(fd);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_95(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
