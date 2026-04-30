#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <libical/ical.h> // Assuming the correct path for the libical headers
}

extern "C" int LLVMFuzzerTestOneInput_461(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to fill an icaltimetype structure
    if (size < sizeof(struct icaltimetype)) {
        return 0;
    }

    // Create an icaltimetype structure from the input data
    struct icaltimetype time;
    memcpy(&time, data, sizeof(struct icaltimetype));

    // Call the function-under-test
    const icaltimezone *timezone = icaltime_get_timezone(time);

    // Use the result (in this case, we just check if it's not NULL)
    if (timezone != NULL) {
        // Optionally, perform additional operations with the timezone
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

    LLVMFuzzerTestOneInput_461(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
