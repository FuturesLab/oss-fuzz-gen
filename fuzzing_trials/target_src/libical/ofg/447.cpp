#include <stdint.h>
#include <stdbool.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for the libical header
}

extern "C" int LLVMFuzzerTestOneInput_447(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to fill the icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize the icaltimetype structure with data from the fuzzer
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    bool result = icaltime_is_null_time(time);

    // Use the result to prevent the compiler from optimizing the call away
    volatile bool prevent_optimization = result;

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

    LLVMFuzzerTestOneInput_447(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
