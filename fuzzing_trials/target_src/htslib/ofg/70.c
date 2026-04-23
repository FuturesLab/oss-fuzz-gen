#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract meaningful data
    if (size < 3) return 0;

    // Create temporary file for fuzzing
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Define mode and format for hts_open_format
    const char *mode = "r"; // Read mode
    htsFormat format;
    memset(&format, 0, sizeof(htsFormat)); // Initialize the format structure

    // Call the function-under-test
    htsFile *file = hts_open_format(tmpl, mode, &format);

    // Clean up
    if (file != NULL) {
        hts_close(file);
    }
    remove(tmpl);

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

    LLVMFuzzerTestOneInput_70(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
