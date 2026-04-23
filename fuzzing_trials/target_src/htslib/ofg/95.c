#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // For mkstemp, write, close, and remove
#include "/src/htslib/htslib/hfile.h" // Correct path for hFILE and hclose

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    hFILE *file = NULL;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd != -1) {
        // Write data to the temporary file
        write(fd, data, size);
        close(fd);

        // Open the file using hopen, which is the correct function to use
        file = hopen(tmpl, "r");

        if (file != NULL) {
            // Call the function-under-test
            hclose(file);
        }

        // Clean up the temporary file
        remove(tmpl);
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

    LLVMFuzzerTestOneInput_95(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
