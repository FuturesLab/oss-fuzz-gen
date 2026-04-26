#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <cstring> // Include the C++ header for memcpy

extern "C" {
    #include <libical/ical.h> // Ensure libical headers are included within extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_1138(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0;
    }

    // Initialize two icaltimetype structures from the input data
    struct icaltimetype time1, time2;

    // Copy data into the first icaltimetype structure
    memcpy(&time1, data, sizeof(struct icaltimetype));

    // Copy data into the second icaltimetype structure
    memcpy(&time2, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Call the function-under-test
    int result = icaltime_compare(time1, time2);

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

    LLVMFuzzerTestOneInput_1138(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
