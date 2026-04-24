#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>

// Function to check if the data is valid ASCII
int is_valid_ascii(const uint8_t *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (data[i] < 32 || data[i] > 126) {
            return 0; // Non-printable ASCII character found
        }
    }
    return 1;
}

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    htsFormat format;
    char *opt_list;

    // Ensure the data is null-terminated to safely convert to a string
    opt_list = (char *)malloc(size + 1);
    if (opt_list == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(opt_list, data, size);
    opt_list[size] = '\0';

    // Check if the data is valid ASCII
    if (!is_valid_ascii(data, size)) {
        free(opt_list);
        return 0; // Exit if data is not valid ASCII
    }

    // Initialize htsFormat structure
    memset(&format, 0, sizeof(htsFormat));

    // Call the function-under-test
    hts_parse_opt_list(&format, opt_list);

    // Clean up
    free(opt_list);

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

    LLVMFuzzerTestOneInput_10(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
