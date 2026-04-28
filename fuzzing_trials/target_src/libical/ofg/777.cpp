#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_777(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Copy the data to a null-terminated string
    char *summary = static_cast<char*>(malloc(size + 1));
    if (summary == nullptr) {
        return 0; // Memory allocation failed
    }
    memcpy(summary, data, size);
    summary[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    icalproperty *property = icalproperty_vanew_summary(summary, nullptr);

    // Clean up
    if (property != nullptr) {
        icalproperty_free(property);
    }
    free(summary);

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

    LLVMFuzzerTestOneInput_777(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
