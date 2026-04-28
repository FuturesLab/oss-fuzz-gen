#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Call the function-under-test
    struct icaldurationtype duration = icaldurationtype_bad_duration();

    // Use the returned duration in some way to ensure it's processed
    // Here, we will simply check if the duration is valid or not
    int is_bad = icaldurationtype_is_bad_duration(duration);

    // Optionally, print the result to verify the behavior
    // This line can be commented out if not needed
    // printf("Is bad duration: %d\n", is_bad);

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

    LLVMFuzzerTestOneInput_11(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
