#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

extern "C" {
    #include <libical/icalcomponent.h>
}

extern "C" int LLVMFuzzerTestOneInput_288(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size == 0 || data[size - 1] != '\0') {
        return 0;
    }

    // Create a new icalcomponent
    icalcomponent *component = icalcomponent_new(ICAL_VEVENT_COMPONENT);
    if (component == NULL) {
        return 0;
    }

    // Cast data to a const char* for the description
    const char *description = reinterpret_cast<const char *>(data);

    // Call the function-under-test
    icalcomponent_set_description(component, description);

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

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_288(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
