#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include for memcpy
#include <unistd.h>  // Include for close and unlink
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    samFile *file = NULL;
    sam_hdr_t *header = NULL;
    int option = 0;  // Initialize with a default option value

    // Create a temporary file to simulate a samFile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;  // If file creation fails, exit
    }

    // Open the temporary file as a samFile
    file = sam_open(tmpl, "w");
    if (file == NULL) {
        close(fd);
        return 0;
    }

    // Initialize a sam_hdr_t object
    header = sam_hdr_init();
    if (header == NULL) {
        sam_close(file);
        close(fd);
        return 0;
    }

    // Set some data in the header using the input data
    if (size > 0) {
        // Use the input data to set the header text
        char *header_text = (char *)malloc(size + 1);
        if (header_text != NULL) {
            memcpy(header_text, data, size);
            header_text[size] = '\0';  // Null-terminate the string
            sam_hdr_add_lines(header, header_text, size);
            free(header_text);
        }
    }

    // Call the function-under-test
    int result = sam_hdr_set(file, header, option);

    // Clean up
    sam_hdr_destroy(header);
    sam_close(file);
    close(fd);
    unlink(tmpl);  // Remove the temporary file

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

    LLVMFuzzerTestOneInput_66(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
