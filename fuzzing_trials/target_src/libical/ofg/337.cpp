#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_337(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a weekday value
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer value from the data
    int weekday_value = *(reinterpret_cast<const int*>(data));

    // Cast the extracted integer to icalrecurrencetype_weekday
    icalrecurrencetype_weekday weekday = static_cast<icalrecurrencetype_weekday>(weekday_value);

    // Call the function-under-test
    const char *weekday_str = icalrecur_weekday_to_string(weekday);

    // Use the result to avoid compiler optimizations that might skip the function call
    if (weekday_str != nullptr) {
        // Do something with weekday_str if needed
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

    LLVMFuzzerTestOneInput_337(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
