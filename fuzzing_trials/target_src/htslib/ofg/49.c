#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>  // For close() and unlink()
#include <fcntl.h>   // For mkstemp()
#include "/src/htslib/htslib/hfile.h"  // Correct path for hfile.h

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    hFILE *hfile = NULL;

    // Ensure size is greater than 0 to create a valid buffer
    if (size > 0) {
        // Create a temporary file with the provided data
        char tmpl[] = "/tmp/fuzzfileXXXXXX";
        int fd = mkstemp(tmpl);
        if (fd != -1) {
            // Write data to the file
            write(fd, data, size);
            // Close the file descriptor to flush the data
            close(fd);

            // Open the file using hopen or similar function from the hFILE library
            hfile = hopen(tmpl, "r");  // Assuming hopen is a function to open hFILE

            // Call the function-under-test
            if (hfile != NULL) {
                hclose_abruptly(hfile);
            }

            // Clean up: remove the temporary file
            unlink(tmpl);
        }
    }

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

    LLVMFuzzerTestOneInput_49(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
