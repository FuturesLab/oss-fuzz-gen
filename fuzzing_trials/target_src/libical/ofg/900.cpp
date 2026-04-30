#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_900(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Convert the input data to a string, ensuring null-termination
    char *inputStr = (char *)malloc(size + 1);
    if (!inputStr) {
        return 0;
    }
    memcpy(inputStr, data, size);
    inputStr[size] = '\0';

    // Use the input string to create a duration
    struct icaldurationtype duration = icaldurationtype_from_string(inputStr);

    // Normally, you would use the output of the function-under-test in some way
    // to ensure it is being tested. Here, we can check if the duration is valid.
    if (!icaldurationtype_is_bad_duration(duration)) {
        // Do something with the valid duration, e.g., convert it back to string
        char *durationStr = icaldurationtype_as_ical_string(duration);
        if (durationStr) {
            // Normally, you might do something with durationStr here
            free(durationStr);
        }
    }

    // Clean up
    free(inputStr);

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

    LLVMFuzzerTestOneInput_900(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
