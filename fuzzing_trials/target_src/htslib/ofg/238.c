#include <stdint.h>
#include <stddef.h>
#include <htslib/hts.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_238(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the filter expression string
    char *filter_expression = (char *)malloc(size + 1);
    if (filter_expression == NULL) {
        return 0;
    }

    // Copy the data into the filter expression and null-terminate it
    memcpy(filter_expression, data, size);
    filter_expression[size] = '\0';

    // Create a dummy htsFile object
    htsFile *hts_file = hts_open("-", "r");
    if (hts_file == NULL) {
        free(filter_expression);
        return 0;
    }

    // Call the function under test with a valid filter expression
    hts_set_filter_expression(hts_file, filter_expression);

    // Clean up
    hts_close(hts_file);
    free(filter_expression);

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

    LLVMFuzzerTestOneInput_238(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
