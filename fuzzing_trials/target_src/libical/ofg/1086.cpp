extern "C" {
    #include <libical/ical.h>
    #include <string.h>
}

#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_1086(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient to create an icaltimetype
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Initialize icaltimetype from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_dtend(time, NULL);

    // Clean up
    if (property != NULL) {
        icalproperty_free(property);
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

    LLVMFuzzerTestOneInput_1086(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
