#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <cstring> // Include for memcpy

extern "C" {
    // Declare the function from the C project
    bool icalrecur_expand_recurrence(const char *, time_t, int, time_t *);
}

extern "C" int LLVMFuzzerTestOneInput_208(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < sizeof(time_t) + sizeof(int) + 1) {
        return 0;
    }

    // Extract a time_t value from the data
    time_t start_time;
    memcpy(&start_time, data, sizeof(time_t));

    // Extract an integer value from the data
    int count;
    memcpy(&count, data + sizeof(time_t), sizeof(int));

    // Use the rest of the data as a string for the recurrence rule
    const char *recur_rule = reinterpret_cast<const char *>(data + sizeof(time_t) + sizeof(int));

    // Allocate memory for the output time_t array
    time_t *expanded_times = static_cast<time_t *>(malloc(count * sizeof(time_t)));
    if (expanded_times == NULL) {
        return 0; // Handle allocation failure
    }

    // Call the function under test
    bool result = icalrecur_expand_recurrence(recur_rule, start_time, count, expanded_times);

    // Clean up
    free(expanded_times);

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

    LLVMFuzzerTestOneInput_208(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
