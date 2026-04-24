#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <htslib/hts.h>

// Assuming DW_TAG_enumeration_typehts_fmt_option is an enum type
typedef enum {
    HTS_FMT_OPTION_1,
    HTS_FMT_OPTION_2,
    HTS_FMT_OPTION_3,
    HTS_FMT_OPTION_MAX
} DW_TAG_enumeration_typehts_fmt_option;

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    htsFile *file = hts_open("temp.bam", "wb");
    if (file == NULL) {
        return 0;
    }

    // Ensure the size is sufficient to extract an option index
    if (size < sizeof(int)) {
        hts_close(file);
        return 0;
    }

    // Extract an option from the data
    int option_index = data[0] % HTS_FMT_OPTION_MAX;
    DW_TAG_enumeration_typehts_fmt_option option = (DW_TAG_enumeration_typehts_fmt_option)option_index;

    // Use a non-NULL pointer for the void* parameter
    int dummy_value = 42;
    void *dummy_ptr = &dummy_value;

    // Call the function-under-test
    hts_set_opt(file, option, dummy_ptr);

    // Clean up
    hts_close(file);
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

    LLVMFuzzerTestOneInput_61(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
