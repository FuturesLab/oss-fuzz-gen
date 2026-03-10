#include <stddef.h>
#include <stdint.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const z_crc_t *crc_table = get_crc_table();

    // Use the crc_table in some way to ensure it is not optimized out
    if (crc_table != NULL && size > 0) {
        // Perform a simple operation using the crc_table
        uint32_t crc_value = crc_table[data[0] % 256];
        (void)crc_value; // Prevent unused variable warning
    }

    return 0;
}