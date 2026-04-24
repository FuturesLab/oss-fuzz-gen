#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include this header for the close() function
#include <htslib/sam.h>
#include <htslib/hts.h>

// Function to create a temporary file with the given data
static char *create_temp_file(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        perror("mkstemp");
        return NULL;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        perror("fdopen");
        close(fd);
        return NULL;
    }
    fwrite(data, 1, size, file);
    fclose(file);
    return strdup(tmpl);
}

int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    char *filename = create_temp_file(data, size);
    if (!filename) {
        return 0;
    }

    htsFile *file = hts_open(filename, "r");
    if (!file) {
        free(filename);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_t *hdr = sam_hdr_read(file);

    // Clean up
    if (hdr) {
        sam_hdr_destroy(hdr);
    }
    hts_close(file);
    free(filename);

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

    LLVMFuzzerTestOneInput_174(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
