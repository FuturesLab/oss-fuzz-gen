#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <libical/ical.h>

extern "C" int LLVMFuzzerTestOneInput_397(const uint8_t *data, size_t size) {
    if (size < sizeof(struct icaltimetype) * 2) {
        return 0;
    }

    struct icalperiodtype period;
    memset(&period, 0, sizeof(struct icalperiodtype));

    // Initialize start and end times from the input data
    memcpy(&period.start, data, sizeof(struct icaltimetype));
    memcpy(&period.end, data + sizeof(struct icaltimetype), sizeof(struct icaltimetype));

    // Call the function-under-test
    char *result = icalperiodtype_as_ical_string_r(period);

    // Free the result if it's not NULL
    if (result != NULL) {
        free(result);
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

    LLVMFuzzerTestOneInput_397(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
