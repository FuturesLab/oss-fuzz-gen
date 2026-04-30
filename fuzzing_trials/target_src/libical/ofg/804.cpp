#include <cstdint>
#include <cstring>

extern "C" {
    #include <libical/ical.h>

    void print_datetime_to_string(char *, const struct icaltimetype *);
}

extern "C" int LLVMFuzzerTestOneInput_804(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid string and icaltimetype
    if (size < sizeof(struct icaltimetype) + 1) {
        return 0;
    }

    // Allocate memory for the output string
    char datetime_str[100];
    memset(datetime_str, 0, sizeof(datetime_str));

    // Prepare an icaltimetype object
    struct icaltimetype datetime;
    memset(&datetime, 0, sizeof(datetime));

    // Copy data into the icaltimetype structure
    memcpy(&datetime, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    print_datetime_to_string(datetime_str, &datetime);

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

    LLVMFuzzerTestOneInput_804(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
