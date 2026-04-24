#include <sys/stat.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function-under-test
ssize_t sam_parse_cigar(const char *cigar_str, char **end, uint32_t **cigar, size_t *n_cigar);

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for string operations
    char *cigar_str = (char *)malloc(size + 1);
    if (cigar_str == NULL) {
        return 0;
    }
    memcpy(cigar_str, data, size);
    cigar_str[size] = '\0';

    // Initialize the other parameters
    char *end = NULL;
    uint32_t *cigar = NULL;
    size_t n_cigar = 0;

    // Call the function-under-test
    ssize_t result = sam_parse_cigar(cigar_str, &end, &cigar, &n_cigar);

    // Clean up
    free(cigar_str);
    free(cigar);

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

    LLVMFuzzerTestOneInput_46(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
