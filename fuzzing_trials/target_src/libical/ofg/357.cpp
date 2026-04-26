#include <cstdint> // For uint8_t
#include <cstddef> // For size_t

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_357(const uint8_t *data, size_t size) {
    // Call the function-under-test
    icalcomponent *component = icalcomponent_new_vresource();

    // Normally, you would do something with the component here.
    // Since this function does not take any input parameters, 
    // and there's no specific way to fuzz it directly with data,
    // we are simply calling it to check for memory issues.

    // Clean up the component to avoid memory leaks
    if (component != NULL) {
        icalcomponent_free(component);
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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_357(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
