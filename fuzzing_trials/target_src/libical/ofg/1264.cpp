#include <cstdint>
#include <cstdio>

// Assuming the function is part of a C library, wrap it in extern "C"
extern "C" {
    short icalrecurrencetype_encode_month(int month, bool leap);
}

extern "C" int LLVMFuzzerTestOneInput_1264(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract both parameters
    if (size < 2) {
        return 0;
    }

    // Extract the first byte for the month parameter
    int month = static_cast<int>(data[0] % 12 + 1); // Ensure month is between 1 and 12

    // Extract the second byte for the leap parameter
    bool leap = static_cast<bool>(data[1] % 2); // Ensure leap is either true or false

    // Call the function-under-test
    short result = icalrecurrencetype_encode_month(month, leap);

    // Print the result for debugging purposes (optional)
    printf("Result: %d\n", result);

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

    LLVMFuzzerTestOneInput_1264(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
