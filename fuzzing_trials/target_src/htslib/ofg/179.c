#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>
#include <htslib/hfile.h>

int LLVMFuzzerTestOneInput_179(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to provide meaningful strings
    if (size < 3) return 0;

    // Create a temporary file to use with hts_hopen
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write the data to the temporary file
    write(fd, data, size);
    close(fd);

    // Prepare the mode and format strings
    const char *mode = "r"; // Read mode
    const char *format = "b"; // Binary format

    // Open the file using hts_hopen
    hFILE *hfile = hopen(tmpl, mode);
    if (hfile == NULL) {
        // Cleanup the temporary file
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    htsFile *hts_file = hts_hopen(hfile, mode, format);

    // Clean up
    if (hts_file != NULL) {
        hts_close(hts_file);
    } else {
        hclose(hfile);
    }

    // Remove the temporary file
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

    LLVMFuzzerTestOneInput_179(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
