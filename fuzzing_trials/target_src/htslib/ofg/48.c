#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // For close() and remove()
#include <htslib/hts.h>
#include <htslib/bgzf.h>
#include <htslib/hts_defs.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    BGZF *bgzf = NULL;
    hts_itr_t *iter = NULL;
    void *data_container = NULL;
    void *aux = NULL;
    int result;

    // Create a temporary file to simulate BGZF input
    char tmpl[] = "/tmp/fuzzbgzfXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the BGZF file
    bgzf = bgzf_open(tmpl, "r");
    if (!bgzf) {
        remove(tmpl);
        return 0;
    }

    // Initialize the iterator
    iter = hts_itr_query(bgzf, 0, 0, 0, 0);
    if (!iter) {
        bgzf_close(bgzf);
        remove(tmpl);
        return 0;
    }

    // Allocate memory for data_container and aux
    data_container = malloc(1024);  // Allocate a buffer for the data
    aux = malloc(1024);  // Allocate a buffer for auxiliary data

    if (data_container && aux) {
        // Call the function under test
        result = hts_itr_next(bgzf, iter, data_container, aux);
    }

    // Clean up
    free(data_container);
    free(aux);
    hts_itr_destroy(iter);
    bgzf_close(bgzf);
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

    LLVMFuzzerTestOneInput_48(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
