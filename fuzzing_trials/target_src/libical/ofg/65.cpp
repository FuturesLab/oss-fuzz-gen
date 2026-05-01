#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include string.h for strlen

extern "C" {
    #include <libical/ical.h> // Adjust the include path to the correct location of libical headers
}

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to represent an icalcomponent_kind
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Cast the input data to icalcomponent_kind
    icalcomponent_kind kind = *(reinterpret_cast<const icalcomponent_kind*>(data));

    // Call the function-under-test
    const char *result = icalcomponent_kind_to_string(kind);

    // Use the result to prevent compiler optimizations from removing the call
    if (result != NULL) {
        // Do something trivial with the result
        volatile size_t len = strlen(result);
        (void)len;
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_65(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
