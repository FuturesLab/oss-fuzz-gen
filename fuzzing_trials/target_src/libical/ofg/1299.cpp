#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memset

extern "C" {
    // Assuming icaltriggertype and icaltriggertype_from_seconds are defined in the C project
    struct icaltriggertype {
        // Define the structure members here as per the C project
    };

    struct icaltriggertype icaltriggertype_from_seconds(const int);
}

extern "C" int LLVMFuzzerTestOneInput_1299(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to form an int
    }

    // Interpret the first 4 bytes of data as an int
    int seconds;
    memcpy(&seconds, data, sizeof(int)); // Use memcpy to safely copy data

    // Check if the seconds value is sensible to avoid potential issues
    if (seconds < 0 || seconds > 1000000) { // Adjust the range as needed
        return 0;
    }

    // Call the function-under-test
    struct icaltriggertype result = icaltriggertype_from_seconds(seconds);

    // Optionally, you can add code here to further process or validate `result`

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

    LLVMFuzzerTestOneInput_1299(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
