#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for splitting into name and value
    if (size < 2) {
        return 0;
    }

    // Initialize GF_ISOFile
    GF_ISOFile *mov = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!mov) {
        return 0;
    }

    // Split the data into two parts for name and value
    size_t name_size = size / 2;
    size_t value_size = size - name_size;

    // Ensure non-zero sizes for name and value
    if (name_size == 0 || value_size == 0) {
        gf_isom_close(mov);
        return 0;
    }

    // Allocate memory for name and value
    char *name = (char *)malloc(name_size + 1);
    char *value = (char *)malloc(value_size + 1);

    if (!name || !value) {
        free(name);
        free(value);
        gf_isom_close(mov);
        return 0;
    }

    // Copy data into name and value, ensuring null-termination
    memcpy(name, data, name_size);
    name[name_size] = '\0';

    memcpy(value, data + name_size, value_size);
    value[value_size] = '\0';

    // Fuzz the function-under-test
    gf_isom_wma_set_tag(mov, name, value);

    // Clean up
    free(name);
    free(value);
    gf_isom_close(mov);

    return 0;
}