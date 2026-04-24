#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "/src/htslib/htslib/sam.h" // Correct path for sam_hdr_t

int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sam_hdr_t *hdr = sam_hdr_init();

    // Check if hdr is initialized successfully
    if (hdr == NULL) {
        return 0;
    }

    // Ensure there is enough data to extract key and value
    if (size < 3) { // Minimum size to have at least a 1-char key and 1-char value
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Use the fuzzing data to create a key-value pair
    size_t key_len = data[0] % (size - 2); // Ensure key length is within bounds
    size_t value_len = size - 2 - key_len; // Remaining data for value

    // Allocate memory for key and value
    char *key = (char *)malloc(key_len + 1);
    char *value = (char *)malloc(value_len + 1);

    if (key == NULL || value == NULL) {
        free(key);
        free(value);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Copy data into key and value, and null-terminate them
    memcpy(key, &data[1], key_len);
    key[key_len] = '\0';
    memcpy(value, &data[1 + key_len], value_len);
    value[value_len] = '\0';

    // Call the function-under-test
    int result = sam_hdr_change_HD(hdr, key, value);

    // Clean up
    free(key);
    free(value);
    sam_hdr_destroy(hdr);

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

    LLVMFuzzerTestOneInput_34(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
