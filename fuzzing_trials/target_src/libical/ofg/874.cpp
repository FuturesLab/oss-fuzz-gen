#include <stdint.h>

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_874(const uint8_t *data, size_t size) {
    // Ensure there is at least one byte to read
    if (size < 1) {
        return 0;
    }

    // Use the first byte of data to create an icalproperty_status value
    // Assuming icalproperty_status is an enum, we can cast the byte to it.
    icalproperty_status status = static_cast<icalproperty_status>(data[0]);

    // Call the function-under-test
    const char *result = icalproperty_status_to_string(status);

    // Use the result to prevent optimization
    if (result) {
        volatile char first_char = result[0];
        (void)first_char;
    }

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

    LLVMFuzzerTestOneInput_874(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
