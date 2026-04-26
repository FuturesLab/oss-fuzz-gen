#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <libical/ical.h>

extern "C" {
    // Function under test
    char *icalperiodtype_as_ical_string_r(struct icalperiodtype period);

    // Correct function to initialize duration
    struct icaldurationtype icaldurationtype_from_string(const char *str);
}

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_396(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to fill the icalperiodtype structure
    if (size < sizeof(struct icalperiodtype)) {
        return 0;
    }

    // Initialize the icalperiodtype structure
    struct icalperiodtype period;
    period.start = icaltime_from_timet_with_zone(time(NULL), 0, NULL);
    period.end = icaltime_from_timet_with_zone(time(NULL) + 3600, 0, NULL);
    
    // Use a valid duration string
    period.duration = icaldurationtype_from_string("PT1H");

    // Call the function under test
    char *result = icalperiodtype_as_ical_string_r(period);

    // Free the result if it was dynamically allocated
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

    LLVMFuzzerTestOneInput_396(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
