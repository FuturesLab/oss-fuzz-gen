#include <stdint.h>
#include <stdlib.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_539(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer value from the input data
    int frequency = *(reinterpret_cast<const int*>(data));

    // Cast the extracted integer to icalrecurrencetype_frequency
    icalrecurrencetype_frequency freq = static_cast<icalrecurrencetype_frequency>(frequency);

    // Call the function-under-test
    const char *result = icalrecur_freq_to_string(freq);

    // Optionally, you can use the result for further checks or logging
    // For example, print the result (in a real fuzzing scenario, you might not print to avoid slowing down the fuzzer)
    // printf("Frequency: %d, Result: %s\n", frequency, result);

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

    LLVMFuzzerTestOneInput_539(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
