#include <libical/ical.h>
#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_868(const uint8_t *data, size_t size) {
    // Initialize the icalproperty and icalparameter objects
    icalproperty *prop = icalproperty_new(ICAL_ANY_PROPERTY);
    icalparameter *param = icalparameter_new(ICAL_ANY_PARAMETER);

    if (prop == NULL || param == NULL) {
        // Cleanup in case of initialization failure
        if (prop != NULL) {
            icalproperty_free(prop);
        }
        if (param != NULL) {
            icalparameter_free(param);
        }
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_parameter(prop, param);

    // Cleanup
    icalproperty_free(prop);
    icalparameter_free(param);

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

    LLVMFuzzerTestOneInput_868(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
