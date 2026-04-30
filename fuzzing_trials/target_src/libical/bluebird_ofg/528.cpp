#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"
#include <cstring>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_528(const uint8_t *data, size_t size) {
    // Ensure that we have at least one byte to interpret as an icalproperty_action
    if (size < 1) {
        return 0;
    }

    // Interpret the first byte of data as an icalproperty_action
    icalproperty_action action = static_cast<icalproperty_action>(data[0]);

    // Call the function-under-test
    const char *result = icalproperty_action_to_string(action);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result != NULL) {
        // Print the result or perform some operation
        // For the sake of this example, we will just do a simple check
        volatile size_t length = std::strlen(result);
        (void)length; // Suppress unused variable warning
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

    LLVMFuzzerTestOneInput_528(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
