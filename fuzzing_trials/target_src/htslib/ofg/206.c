#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Include for close() and remove()
#include <htslib/hts.h>
#include <htslib/hfile.h>

int LLVMFuzzerTestOneInput_206(const uint8_t *data, size_t size) {
    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file using hFILE
    hFILE *hfile = hopen(tmpl, "rb");
    if (hfile == NULL) {
        remove(tmpl);
        return 0;
    }

    // Prepare a format string and htsFormat structure
    const char *format_str = "r";
    htsFormat format;

    // Call the function under test
    hts_detect_format2(hfile, format_str, &format);

    // Cleanup
    hclose(hfile);
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

    LLVMFuzzerTestOneInput_206(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
