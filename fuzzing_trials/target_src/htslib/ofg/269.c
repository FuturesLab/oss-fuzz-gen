#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Assume the function is declared in some header file
uint32_t hts_crc32(uint32_t crc, const void *buf, size_t len);

int LLVMFuzzerTestOneInput_269(const uint8_t *data, size_t size) {
    // Initialize crc with a non-zero value for better testing coverage
    uint32_t crc = 0xFFFFFFFF;

    // Call the function-under-test with the provided data
    uint32_t result = hts_crc32(crc, (const void *)data, size);

    // Optionally print the result for debugging purposes
    printf("CRC32 Result: %u\n", result);

    return 0;
}