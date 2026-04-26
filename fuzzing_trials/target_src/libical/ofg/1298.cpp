#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy and strlen

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1298(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to fill the icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icaltimetype instance and initialize it with data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    const char *result = icaltime_as_ical_string(time);

    // Use the result to prevent it from being optimized away
    if (result != NULL) {
        // For example, we could check the length of the resulting string
        size_t result_length = strlen(result);
        (void)result_length; // Suppress unused variable warning
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

    LLVMFuzzerTestOneInput_1298(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
