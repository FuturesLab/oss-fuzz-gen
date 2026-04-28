#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_338(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first bytes of data as an integer for the weekday
    int weekday = *(reinterpret_cast<const int*>(data));

    // Cast the integer to icalrecurrencetype_weekday
    icalrecurrencetype_weekday weekday_enum = static_cast<icalrecurrencetype_weekday>(weekday);

    // Call the function-under-test
    const char *result = icalrecur_weekday_to_string(weekday_enum);

    // Use the result to prevent compiler optimizations that remove the call
    if (result != nullptr) {
        volatile const char *volatile_result = result;
        (void)volatile_result;
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

    LLVMFuzzerTestOneInput_338(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
