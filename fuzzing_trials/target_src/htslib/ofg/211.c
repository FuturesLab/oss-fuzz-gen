#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

extern uint32_t hts_crc32(uint32_t crc, const void *buf, size_t len);

int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    // Initialize the crc value to a non-zero constant
    uint32_t crc = 0xFFFFFFFF;

    // Call the function-under-test
    uint32_t result = hts_crc32(crc, (const void *)data, size);

    // Print the result to verify the function call (optional for debugging)
    printf("CRC32 Result: %u\n", result);

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

    LLVMFuzzerTestOneInput_211(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
