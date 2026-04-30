#include <libical/ical.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_930(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to create a non-empty string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the string and ensure it is null-terminated
    char *grant_str = static_cast<char *>(malloc(size + 1));
    if (grant_str == nullptr) {
        return 0;
    }
    memcpy(grant_str, data, size);
    grant_str[size] = '\0';

    // Create a dummy parameter to pass as the varargs to the function-under-test
    icalparameter *param = icalparameter_new(ICAL_ANY_PARAMETER);

    // Call the function-under-test with non-null additional parameters
    icalproperty *prop = icalproperty_vanew_grant(grant_str, param, nullptr);

    // Clean up
    if (prop != nullptr) {
        icalproperty_free(prop);
    }
    if (param != nullptr) {
        icalparameter_free(param);
    }
    free(grant_str);

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

    LLVMFuzzerTestOneInput_930(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
