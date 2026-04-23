#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/hts.h"

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize htsFormat structure
    htsFormat format;
    
    // Ensure that the size is large enough to fill the fields of htsFormat
    if (size < sizeof(htsFormat)) {
        return 0;
    }

    // Copy data to format, ensuring no overflow
    memcpy(&format, data, sizeof(htsFormat));

    // Call the function-under-test
    char *description = hts_format_description(&format);

    // Free the allocated description if it's not NULL
    if (description != NULL) {
        free(description);
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_21(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
