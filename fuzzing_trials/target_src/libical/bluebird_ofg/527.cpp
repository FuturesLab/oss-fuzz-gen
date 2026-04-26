#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include "libical/ical.h"
#include <string.h> // Include the necessary header for strlen

extern "C" {
    // Wrap the libical includes and functions in extern "C" to ensure proper linkage
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_527(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an icalproperty_class value
    if (size < sizeof(icalproperty_class)) {
        return 0;
    }

    // Extract an icalproperty_class value from the input data
    icalproperty_class prop_class = static_cast<icalproperty_class>(data[0]);

    // Call the function-under-test
    const char *result = icalproperty_class_to_string(prop_class);

    // Use the result in some way to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Just a simple operation to use the result
        volatile size_t length = strlen(result);
        (void)length;
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

    LLVMFuzzerTestOneInput_527(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
