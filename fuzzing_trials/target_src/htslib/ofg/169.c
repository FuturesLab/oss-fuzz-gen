#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For close() and unlink()
#include <fcntl.h>  // For mkstemp()
#include "/src/htslib/htslib/hfile.h" // Correct path for hFILE

// Remove the extern "C" linkage specification as it is not needed in C
int LLVMFuzzerTestOneInput_169(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Need at least 2 bytes for delimiter and data
    }

    // Allocate a buffer for the line
    size_t buffer_size = 1024;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        return 0; // Handle allocation failure
    }

    // Use the first byte of data as the delimiter
    int delimiter = data[0];

    // Create a temporary file and write the remaining data to it
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        free(buffer);
        return 0; // Handle file creation failure
    }
    FILE *fp = fdopen(fd, "wb+");
    if (fp == NULL) {
        close(fd);
        free(buffer);
        return 0; // Handle file opening failure
    }
    fwrite(data + 1, 1, size - 1, fp);
    rewind(fp);

    // Convert FILE* to hFILE* using hdopen
    hFILE *hfile = hdopen(fd, "rb");
    if (hfile == NULL) {
        fclose(fp);
        free(buffer);
        return 0; // Handle hFILE creation failure
    }

    // Call the function-under-test
    ssize_t result = hgetdelim(buffer, buffer_size, delimiter, hfile);

    // Clean up
    hclose(hfile);
    fclose(fp);
    free(buffer);
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

    LLVMFuzzerTestOneInput_169(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
