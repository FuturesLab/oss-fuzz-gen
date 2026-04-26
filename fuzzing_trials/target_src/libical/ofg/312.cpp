#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

extern "C" {
    // Declare the function signature for the function-under-test
    struct icaltimetype {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        int is_date;
        int is_utc;
        int is_valid;
        int is_daylight;
    };

    struct icaltimetype icaltime_from_string(const char *);
}

extern "C" int LLVMFuzzerTestOneInput_312(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to safely convert it to a C-string
    char *cstr = (char *)malloc(size + 1);
    if (cstr == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(cstr, data, size);
    cstr[size] = '\0';

    // Call the function-under-test
    struct icaltimetype result = icaltime_from_string(cstr);

    // Clean up
    free(cstr);

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

    LLVMFuzzerTestOneInput_312(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
