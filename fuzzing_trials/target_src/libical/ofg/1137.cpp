#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1137(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a valid icalproperty
    if (size < 1) {
        return 0;
    }

    // Create a temporary buffer to null-terminate the input data
    char *buffer = static_cast<char *>(malloc(size + 1));
    if (buffer == nullptr) {
        return 0;
    }
    memcpy(buffer, data, size);
    buffer[size] = '\0';

    // Parse the buffer into an icalproperty
    icalproperty *property = icalproperty_new_from_string(buffer);

    if (property != nullptr) {
        // Call the function-under-test
        const char *link = icalproperty_get_link(property);

        // Optionally, do something with the result to avoid compiler optimizations
        if (link != nullptr) {
            // For example, just print the link (in a real fuzzing environment, this line might be omitted)
            printf("Link: %s\n", link);
        }

        // Free the icalproperty
        icalproperty_free(property);
    }

    // Free the temporary buffer
    free(buffer);

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

    LLVMFuzzerTestOneInput_1137(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
