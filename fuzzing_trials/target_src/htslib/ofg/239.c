#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <string.h>

int LLVMFuzzerTestOneInput_239(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a meaningful string
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to act as the htsFile
    const char *filename = "/tmp/fuzz_htsfile.bam";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(filename, "r");
    if (!hts_file) {
        return 0;
    }

    // Create a null-terminated string from the data for the filter expression
    char *filter_expression = (char *)malloc(size + 1);
    if (!filter_expression) {
        hts_close(hts_file);
        return 0;
    }
    memcpy(filter_expression, data, size);
    filter_expression[size] = '\0';

    // Call the function-under-test
    hts_set_filter_expression(hts_file, filter_expression);

    // Clean up
    free(filter_expression);
    hts_close(hts_file);
    remove(filename);

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

    LLVMFuzzerTestOneInput_239(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
