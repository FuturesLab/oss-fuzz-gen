#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/kstring.h" // Include this if needed for hts_set_opt options

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    htsFile *file = hts_open("-", "r");
    enum hts_fmt_option option = (enum hts_fmt_option)(data[0] % 5); // Assuming 5 is the number of possible options
    int value = (size > 1) ? data[1] : 0; // Use the second byte as a value, if available

    if (file != NULL) {
        hts_set_opt(file, option, (void *)(uintptr_t)value);
        hts_close(file);
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

    LLVMFuzzerTestOneInput_92(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
