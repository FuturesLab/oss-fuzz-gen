#include <libical/ical.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *data, size_t size) {
    // Ensure that the size of the data is sufficient to create a timezone
    if (size < 1) {
        return 0;
    }

    // Create a temporary string from the input data to use as a timezone ID
    char timezone_id[256];
    size_t id_length = size < 255 ? size : 255;
    for (size_t i = 0; i < id_length; ++i) {
        timezone_id[i] = static_cast<char>(data[i] % 128); // Ensure valid ASCII
    }
    timezone_id[id_length] = '\0';

    // Create a timezone using the generated ID
    icaltimezone *timezone = icaltimezone_get_builtin_timezone(timezone_id);

    // Call the function-under-test
    icalcomponent *component = icaltimezone_get_component(timezone);

    // Clean up
    // Note: icaltimezone_get_builtin_timezone does not require freeing the timezone

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

    LLVMFuzzerTestOneInput_138(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
