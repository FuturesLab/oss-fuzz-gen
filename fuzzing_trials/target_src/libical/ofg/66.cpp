#include <stdint.h>
#include <stddef.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an icalcomponent_kind value
    if (size < sizeof(icalcomponent_kind)) {
        return 0;
    }

    // Extract an icalcomponent_kind value from the input data
    icalcomponent_kind kind = static_cast<icalcomponent_kind>(data[0]);

    // Call the function-under-test
    const char *result = icalcomponent_kind_to_string(kind);

    // Use the result to avoid compiler optimizations removing the call
    if (result != nullptr) {
        volatile char c = result[0];
        (void)c;
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

    LLVMFuzzerTestOneInput_66(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
