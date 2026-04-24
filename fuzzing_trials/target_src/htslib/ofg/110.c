#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <openssl/md5.h> // Include the necessary library for MD5 functions

// Function prototype
void hts_md5_hex_110(char *hex, const unsigned char *data, size_t size) {
    unsigned char md5_result[MD5_DIGEST_LENGTH];
    MD5(data, size, md5_result); // Compute MD5 hash with the provided size

    // Convert the MD5 hash to a hex string
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&hex[i * 2], "%02x", md5_result[i]);
    }
}

int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    // Ensure there's enough data to process
    if (size < 1) { // Allow processing of any non-zero size input
        return 0;
    }

    // Allocate memory for the output hex string (32 characters + 1 for null terminator)
    char hex[33];
    hex[32] = '\0'; // Null-terminate the string

    // Call the function-under-test with the actual size of the data
    hts_md5_hex_110(hex, data, size);

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

    LLVMFuzzerTestOneInput_110(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
