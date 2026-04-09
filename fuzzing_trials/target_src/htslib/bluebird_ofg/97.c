#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"

// Function prototype for the hypothetical hts_opt functions
typedef struct hts_opt hts_opt;
int hts_opt_add(hts_opt **opt, const char *opt_str);
void hts_opt_free(hts_opt *opt);

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for hts_opt pointer
    hts_opt *opt = NULL;

    // Allocate memory for a null-terminated string
    char *opt_str = (char *)malloc(size + 1);
    if (opt_str == NULL) {
        return 0;
    }

    // Copy the input data to opt_str and null-terminate it
    memcpy(opt_str, data, size);
    opt_str[size] = '\0';

    // Call the function-under-test
    hts_opt_add(&opt, opt_str);

    // Clean up
    free(opt_str);
    hts_opt_free(opt);

    return 0;
}