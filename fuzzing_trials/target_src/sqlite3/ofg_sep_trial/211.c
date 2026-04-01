#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>  // Include this for malloc and free
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    if (size < 3) return 0; // Ensure there is enough data for three parts

    // Split the data into three parts
    size_t part1_size = size / 3;
    size_t part2_size = size / 3;
    size_t part3_size = size - part1_size - part2_size;

    // Ensure each part has at least one byte
    if (part1_size == 0 || part2_size == 0 || part3_size == 0) return 0;

    // Allocate memory for the strings
    char *str1 = (char *)malloc(part1_size + 1);
    char *str2 = (char *)malloc(part2_size + 1);

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(str1, data, part1_size);
    str1[part1_size] = '\0';

    memcpy(str2, data + part1_size, part2_size);
    str2[part2_size] = '\0';

    // Use the third part as the integer argument for comparison length
    int n = (int)(data[part1_size + part2_size] % 256);

    // Call the function under test
    int result = sqlite3_strnicmp(str1, str2, n);

    // Clean up
    free(str1);
    free(str2);

    return 0;
}