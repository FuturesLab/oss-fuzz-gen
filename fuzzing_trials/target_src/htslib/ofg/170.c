#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <htslib/hts.h>

// Define a dummy enumeration for DW_TAG_enumeration_typehts_fmt_option
typedef enum {
    HTS_FMT_OPTION_1,
    HTS_FMT_OPTION_2,
    HTS_FMT_OPTION_3,
    HTS_FMT_OPTION_MAX
} DW_TAG_enumeration_typehts_fmt_option;

int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for our needs
    if (size < sizeof(int)) {
        return 0;
    }

    // Create a temporary htsFile object
    htsFile *file = hts_open("test.tmp", "w");
    if (!file) {
        return 0;
    }

    // Extract an option from the data
    DW_TAG_enumeration_typehts_fmt_option option = (DW_TAG_enumeration_typehts_fmt_option)(data[0] % HTS_FMT_OPTION_MAX);

    // Use the rest of the data as the void* parameter
    void *opt_data = (void *)(data + 1);

    // Call the function under test
    int result = hts_set_opt(file, option, opt_data);

    // Clean up
    hts_close(file);
    remove("test.tmp");

    return 0;
}