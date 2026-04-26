#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Wrap the C library includes with extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_823(const uint8_t *data, size_t size) {
    // Ensure there is enough data to populate the required structures
    if (size < sizeof(struct icaltimetype) + sizeof(int)) {
        return 0;
    }

    // Initialize a timezone object
    icaltimezone *timezone = icaltimezone_new(); // Create a new timezone object

    // Initialize an icaltimetype object from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Initialize an int for the UTC offset
    int offset;
    memcpy(&offset, data + sizeof(struct icaltimetype), sizeof(int));

    // Call the function-under-test
    int result = icaltimezone_get_utc_offset_of_utc_time(timezone, &time, &offset);

    // Clean up
    icaltimezone_free(timezone, 1); // Provide the second argument as per the function signature

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

    LLVMFuzzerTestOneInput_823(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
