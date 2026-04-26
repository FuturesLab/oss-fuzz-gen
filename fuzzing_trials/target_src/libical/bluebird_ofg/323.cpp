#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"

extern "C" {
    // Include necessary C headers and function declarations
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_323(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to extract a value for ical_unknown_token_handling
    if (size < sizeof(ical_unknown_token_handling)) {
        return 0;
    }

    // Extract a value from the input data for ical_unknown_token_handling
    ical_unknown_token_handling handling_setting = static_cast<ical_unknown_token_handling>(data[0] % 3);

    // Call the function-under-test with the extracted value
    ical_set_unknown_token_handling_setting(handling_setting);

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

    LLVMFuzzerTestOneInput_323(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
