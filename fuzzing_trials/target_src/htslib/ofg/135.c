#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> // Include string.h for memset
#include "/src/htslib/htslib/hfile.h"

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    hFILE *file = NULL;
    off_t offset;
    int whence;
    off_t result;

    // Ensure size is sufficient to extract necessary parameters
    if (size < sizeof(off_t) + sizeof(int)) {
        return 0;
    }

    // Create a temporary file to use with hseek
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

    // Open the file using hfile
    file = hopen(tmpl, "r");
    if (file == NULL) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Extract parameters from data
    offset = *(off_t *)(data);
    whence = *(int *)(data + sizeof(off_t));

    // Call the function-under-test
    result = hseek(file, offset, whence);

    // Clean up
    hclose(file);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_135(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
