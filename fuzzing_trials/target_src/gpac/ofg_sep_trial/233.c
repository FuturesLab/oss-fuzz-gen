#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

// Mock function to simulate GF_ISOFile creation
GF_ISOFile* create_mock_iso_file() {
    // Properly initialize a GF_ISOFile object
    GF_ISOFile *file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

int LLVMFuzzerTestOneInput_233(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for splitting into name and value
    if (size < 2) return 0;

    // Create a mock GF_ISOFile object
    GF_ISOFile *mov = create_mock_iso_file();
    if (!mov) return 0;

    // Split the input data into two parts for name and value
    size_t name_len = size / 2;
    size_t value_len = size - name_len;

    // Allocate memory for name and value strings
    char *name = (char*)malloc(name_len + 1);
    char *value = (char*)malloc(value_len + 1);

    if (!name || !value) {
        if (mov) gf_isom_close(mov);
        free(name);
        free(value);
        return 0;
    }

    // Copy data into name and value, ensuring null-termination
    memcpy(name, data, name_len);
    name[name_len] = '\0';

    memcpy(value, data + name_len, value_len);
    value[value_len] = '\0';

    // Call the function-under-test
    gf_isom_wma_set_tag(mov, name, value);

    // Clean up
    gf_isom_close(mov);
    free(name);
    free(value);

    return 0;
}