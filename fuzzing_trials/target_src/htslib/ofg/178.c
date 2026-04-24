#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/hfile.h>

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Ensure there is enough data for the required strings
    }

    // Create a temporary file to simulate hFILE input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the hFILE
    hFILE *hfile = hopen(tmpl, "rb");
    if (hfile == NULL) {
        unlink(tmpl);
        return 0; // Failed to open hFILE
    }

    // Prepare the mode and format strings
    const char *mode = "r";
    const char *format = "b";

    // Call the function-under-test
    htsFile *htsfile = hts_hopen(hfile, mode, format);

    // Clean up
    if (htsfile != NULL) {
        hts_close(htsfile);
    }
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

    LLVMFuzzerTestOneInput_178(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
