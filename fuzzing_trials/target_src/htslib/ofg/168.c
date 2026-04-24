#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for close and unlink
#include <fcntl.h>  // Include for mkstemp
#include "/src/htslib/htslib/hfile.h" // Correct path for hfile.h

int LLVMFuzzerTestOneInput_168(const uint8_t *data, size_t size) {
    // Ensure the data is large enough for meaningful testing
    if (size < 2) return 0;

    // Create a temporary file and write the fuzz data to it
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    FILE *file = fdopen(fd, "wb+");
    if (file == NULL) {
        close(fd);
        return 0;
    }

    fwrite(data, 1, size, file);
    fflush(file);
    fseek(file, 0, SEEK_SET);

    // Open the file using hts_open, which is a valid function in htslib
    hFILE *hfile = hopen(tmpl, "rb");
    if (hfile == NULL) {
        fclose(file);
        return 0;
    }

    // Allocate a buffer for hgetdelim
    size_t buffer_size = size + 1;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        hclose(hfile);
        fclose(file);
        return 0;
    }

    // Call the function-under-test
    ssize_t result = hgetdelim(buffer, buffer_size, '\n', hfile);

    // Clean up
    free(buffer);
    hclose(hfile);
    fclose(file);
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

    LLVMFuzzerTestOneInput_168(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
