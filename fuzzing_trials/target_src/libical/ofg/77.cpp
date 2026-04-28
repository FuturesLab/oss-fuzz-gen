extern "C" {
    #include <libical/ical.h>
    #include <libical/icalrecur.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Declare and initialize the icalrecurrencetype structure
    struct icalrecurrencetype recurrence;
    memset(&recurrence, 0, sizeof(recurrence));

    // Ensure that the size is sufficient to fill the structure
    if (size < sizeof(recurrence)) {
        return 0;
    }

    // Copy data into the recurrence structure
    memcpy(&recurrence, data, sizeof(recurrence));

    // Define ICAL_RECURRENCE_ARRAY_MAX since the header is missing
    const int ICAL_RECURRENCE_ARRAY_MAX = 10; // Assuming a max value for demonstration

    // Validate the recurrence structure before using it
    if (recurrence.freq <= ICAL_NO_RECURRENCE || recurrence.freq >= ICAL_RECURRENCE_ARRAY_MAX) {
        return 0;
    }

    // Call the function-under-test
    char *result = icalrecurrencetype_as_string(&recurrence);

    // Free the result if it's not NULL
    if (result != nullptr) {
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

    LLVMFuzzerTestOneInput_77(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
