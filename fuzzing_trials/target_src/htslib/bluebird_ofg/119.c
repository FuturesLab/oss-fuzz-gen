#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For close() and unlink()
#include <fcntl.h>  // For mkstemp()
#include "htslib/hts.h"
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    char tmpl1[] = "/tmp/fuzzfileXXXXXX";
    char tmpl2[] = "/tmp/fuzzfileXXXXXX";
    char tmpl3[] = "/tmp/fuzzfileXXXXXX";
    int fd1 = mkstemp(tmpl1);
    int fd2 = mkstemp(tmpl2);
    int fd3 = mkstemp(tmpl3);

    if (fd1 == -1 || fd2 == -1 || fd3 == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary files
    write(fd1, data, size);
    write(fd2, data, size);
    write(fd3, data, size);

    // Open the first file as an htsFile
    htsFile *hts_file = hts_open(tmpl1, "r");
    if (hts_file == NULL) {
        close(fd1);
        close(fd2);
        close(fd3);
        return 0;
    }

    // Call the function-under-test
    hts_idx_t *index = sam_index_load2(hts_file, tmpl2, tmpl3);

    // Clean up
    if (index != NULL) {
        hts_idx_destroy(index);
    }
    hts_close(hts_file);
    close(fd1);
    close(fd2);
    close(fd3);
    unlink(tmpl1);
    unlink(tmpl2);
    unlink(tmpl3);

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

    LLVMFuzzerTestOneInput_119(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
