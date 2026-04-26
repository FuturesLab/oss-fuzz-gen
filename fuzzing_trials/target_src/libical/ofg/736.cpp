#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

// Wrap the necessary C headers and declarations in extern "C"
extern "C" {
    #include <libical/ical.h>

    void print_date_to_string(char *, const struct icaltimetype *);
}

extern "C" int LLVMFuzzerTestOneInput_736(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a valid date string and icaltimetype
    if (size < 20) {
        return 0;
    }

    // Allocate and initialize a buffer for the date string
    char date_str[20];
    memset(date_str, 0, sizeof(date_str));

    // Create an icaltimetype structure
    struct icaltimetype time;

    // Populate the icaltimetype fields using the input data
    time.year = (int)data[0] + 1900;  // Year range from 1900 to 2155
    time.month = (int)(data[1] % 12) + 1;  // Month range from 1 to 12
    time.day = (int)(data[2] % 31) + 1;  // Day range from 1 to 31
    time.hour = (int)(data[3] % 24);  // Hour range from 0 to 23
    time.minute = (int)(data[4] % 60);  // Minute range from 0 to 59
    time.second = (int)(data[5] % 60);  // Second range from 0 to 59
    time.is_date = (int)(data[6] % 2);  // is_date can be 0 or 1
    time.is_daylight = (int)(data[7] % 2);  // is_daylight can be 0 or 1
    time.zone = NULL;  // Set zone to NULL for simplicity

    // Call the function-under-test
    print_date_to_string(date_str, &time);

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

    LLVMFuzzerTestOneInput_736(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
