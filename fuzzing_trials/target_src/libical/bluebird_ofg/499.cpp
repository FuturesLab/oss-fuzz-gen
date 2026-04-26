#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // Include this header to define size_t

// Assuming the function is defined in a C library, we need to wrap it with extern "C"
extern "C" {
    short icalrecurrencetype_encode_month(int month, bool leap_year);
}

extern "C" int LLVMFuzzerTestOneInput_499(const uint8_t *data, size_t size) {
    // Ensure the size is adequate to extract the necessary parameters
    if (size < 2) {
        return 0;
    }

    // Extract the first byte as an integer for the month
    int month = static_cast<int>(data[0]) % 12 + 1; // Ensure month is between 1 and 12

    // Extract the second byte as a boolean for leap_year
    bool leap_year = static_cast<bool>(data[1] % 2);

    // Call the function-under-test
    short result = icalrecurrencetype_encode_month(month, leap_year);

    // Return 0 to indicate successful execution
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

    LLVMFuzzerTestOneInput_499(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
