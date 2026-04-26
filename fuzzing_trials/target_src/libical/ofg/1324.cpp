extern "C" {
    #include <libical/ical.h>
    #include <stdint.h>
    #include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput_1324(const uint8_t *data, size_t size) {
    // Call the function-under-test
    struct icaltimetype today = icaltime_today();

    // Use the result in some way to prevent any compiler optimizations from removing the call
    if (icaltime_is_valid_time(today)) {
        // For fuzzing purposes, we can perform some operation with the result
        const char *today_str = icaltime_as_ical_string(today);
        if (today_str != NULL) {
            // Normally, you might do something with today_str, but for fuzzing, we just ensure it is not NULL
            icalmemory_free_buffer((void*)today_str);
        }
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

    LLVMFuzzerTestOneInput_1324(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
