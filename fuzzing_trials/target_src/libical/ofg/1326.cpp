#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_1326(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to safely convert to a string
    if (size == 0) return 0;

    // Create a buffer to hold the null-terminated string
    char *input = (char *)malloc(size + 1);
    if (!input) return 0;
    memcpy(input, data, size);
    input[size] = '\0';

    // Call the function-under-test
    struct icaltimetype result = icaltime_from_string(input);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result.is_date) {
        // This block is just to ensure the result is used
        free(input);
        return 1;
    }

    free(input);
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

    LLVMFuzzerTestOneInput_1326(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
