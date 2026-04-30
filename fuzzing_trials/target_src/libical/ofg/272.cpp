#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_272(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be meaningful
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *inputData = static_cast<char*>(malloc(size + 1));
    if (inputData == nullptr) {
        return 0;
    }
    memcpy(inputData, data, size);
    inputData[size] = '\0';

    // Create a timezone from the input data
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(inputData);

    // Fuzz the function-under-test
    const char *tzid = icaltimezone_get_tzid(timezone);

    // Output the result for debugging purposes
    if (tzid != nullptr) {
        std::cout << "Timezone ID: " << tzid << std::endl;
    }

    // Clean up
    free(inputData);

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

    LLVMFuzzerTestOneInput_272(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
