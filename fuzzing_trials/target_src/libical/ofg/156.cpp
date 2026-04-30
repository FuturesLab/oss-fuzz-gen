#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a null-terminated string
    if (size == 0) return 0;

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) return 0;

    // Create a null-terminated string from the input data
    char *relcalid = (char *)malloc(size + 1);
    if (relcalid == NULL) {
        icalcomponent_free(component);
        return 0;
    }
    memcpy(relcalid, data, size);
    relcalid[size] = '\0';

    // Call the function-under-test
    icalcomponent_set_relcalid(component, relcalid);

    // Clean up
    free(relcalid);
    icalcomponent_free(component);

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

    LLVMFuzzerTestOneInput_156(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
