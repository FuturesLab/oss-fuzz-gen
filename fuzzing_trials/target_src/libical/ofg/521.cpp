#include <libical/ical.h>
#include <cstdint>
#include <cstring>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_521(const uint8_t *data, size_t size) {
    // Ensure that the data is large enough to be useful
    if (size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *param_name = static_cast<char*>(malloc(size + 1));
    if (param_name == nullptr) {
        return 0;
    }
    memcpy(param_name, data, size);
    param_name[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    icalproperty *prop = icalproperty_vanew_patchparameter(param_name, nullptr);

    // Clean up
    if (prop != nullptr) {
        icalproperty_free(prop);
    }
    free(param_name);

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

    LLVMFuzzerTestOneInput_521(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
