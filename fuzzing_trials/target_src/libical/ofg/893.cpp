#include <stddef.h>
#include <stdint.h>
#include <cstring> // Include this for strlen

extern "C" {
#include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_893(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to extract an icalproperty_action value
    if (size < sizeof(icalproperty_action)) {
        return 0;
    }

    // Extract an icalproperty_action value from the input data
    icalproperty_action action = static_cast<icalproperty_action>(data[0]);

    // Call the function-under-test
    const char *result = icalproperty_action_to_string(action);

    // Use the result to avoid compiler optimizations removing the call
    if (result != NULL) {
        size_t length = strlen(result);
        // Do something with length if needed
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

    LLVMFuzzerTestOneInput_893(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
