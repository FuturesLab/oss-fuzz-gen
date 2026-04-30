#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <libical/ical.h> // Correctly include the libical header

    // Function signature for the function-under-test
    void icalcomponent_set_method(icalcomponent *, icalproperty_method);
}

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // Initialize variables before goto
    icalcomponent *component = nullptr;
    icalproperty_method method;

    // Ensure there is enough data to extract a method value
    if (size < sizeof(icalproperty_method)) {
        return 0;
    }

    // Create a new icalcomponent
    component = icalcomponent_new(ICAL_VCALENDAR_COMPONENT);
    if (component == nullptr) {
        return 0;
    }

    // Extract a method value from the input data
    method = static_cast<icalproperty_method>(data[0] % ICAL_METHOD_NONE);

    // Call the function-under-test
    icalcomponent_set_method(component, method);

    // Clean up
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

    LLVMFuzzerTestOneInput_89(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
