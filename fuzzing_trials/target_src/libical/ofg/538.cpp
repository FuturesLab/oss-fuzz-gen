#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h>
    #include <libical/icalrecur.h>
}

// Ensure that the input size is sufficient to extract an integer value
extern "C" int LLVMFuzzerTestOneInput_538(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    // Interpret the first bytes of data as an integer for frequency
    icalrecurrencetype_frequency freq = static_cast<icalrecurrencetype_frequency>(data[0] % ICAL_SECONDLY_RECURRENCE);

    // Call the function-under-test
    const char *result = icalrecur_freq_to_string(freq);

    // Optionally, do something with the result (e.g., print it, check it)
    // For fuzzing, we typically don't need to do anything with the result

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

    LLVMFuzzerTestOneInput_538(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
