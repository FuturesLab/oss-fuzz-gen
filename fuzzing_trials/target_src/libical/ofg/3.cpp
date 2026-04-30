#include <cstdint> // For uint8_t
#include <cstddef> // For size_t

extern "C" {
    // Declare the function prototype for the function under test.
    int icalrecurrencetype_day_position(short day_position);
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Declare and initialize the short variable to be passed to the function
    short day_position;

    // Ensure the size is sufficient to extract a short value
    if (size < sizeof(short)) {
        return 0; // Not enough data to proceed
    }

    // Extract a short value from the input data
    day_position = *(reinterpret_cast<const short*>(data));

    // Call the function-under-test
    int result = icalrecurrencetype_day_position(day_position);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

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

    LLVMFuzzerTestOneInput_3(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
