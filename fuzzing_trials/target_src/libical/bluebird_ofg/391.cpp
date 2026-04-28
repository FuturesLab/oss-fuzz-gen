#include <string.h>
#include <sys/stat.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {
    // Include the necessary header for the function-under-test
    #include "/src/libical/src/libical/icaltimezone.h"
}

extern "C" int LLVMFuzzerTestOneInput_391(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated before passing it to the function
    char *tzid_prefix = new char[size + 1];
    if (tzid_prefix == nullptr) {
        return 0; // Handle allocation failure
    }

    // Copy the input data to the tzid_prefix and null-terminate it
    std::memcpy(tzid_prefix, data, size);
    tzid_prefix[size] = '\0';

    // Call the function-under-test
    icaltimezone_set_tzid_prefix(tzid_prefix);

    // Clean up
    delete[] tzid_prefix;

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

    LLVMFuzzerTestOneInput_391(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
