#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

// Wrap the necessary C headers and functions in extern "C"
extern "C" {
    #include <libical/ical.h> // Correctly include the necessary header from the libical library

    // Function-under-test declaration
    void print_datetime_to_string(char *buffer, const struct icaltimetype *time);
}

extern "C" int LLVMFuzzerTestOneInput_803(const uint8_t *data, size_t size) {
    // Ensure there is enough data to fill the icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Allocate a buffer for the output string
    char output_buffer[100]; // Arbitrary size for storing the formatted date-time string

    // Initialize the icaltimetype structure with data from the fuzzing input
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Ensure the buffer is not NULL and call the function-under-test
    print_datetime_to_string(output_buffer, &time);

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

    LLVMFuzzerTestOneInput_803(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
