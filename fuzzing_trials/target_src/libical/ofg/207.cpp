#include <cstdint>
#include <ctime>
#include <cstring>
#include <cstdlib>

// Since "icalrecur.h" does not exist, we need to declare the function signature
// for icalrecur_expand_recurrence. We assume the following signature based on the usage.
extern "C" {
    bool icalrecur_expand_recurrence(const char *rule, time_t start, int count, time_t *times);
}

extern "C" int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    if (size < sizeof(time_t) + sizeof(int)) {
        return 0;
    }

    // Extract a time_t value from the data
    time_t start_time;
    std::memcpy(&start_time, data, sizeof(time_t));

    // Extract an int value from the data
    int count;
    std::memcpy(&count, data + sizeof(time_t), sizeof(int));

    // Ensure there's enough data left for a string and time_t array
    if (size <= sizeof(time_t) + sizeof(int)) {
        return 0;
    }

    // Calculate the length of the string
    size_t str_len = size - sizeof(time_t) - sizeof(int);
    
    // Allocate memory for the string and null-terminate it
    char *recurrence_rule = static_cast<char*>(malloc(str_len + 1));
    if (!recurrence_rule) {
        return 0;
    }
    std::memcpy(recurrence_rule, data + sizeof(time_t) + sizeof(int), str_len);
    recurrence_rule[str_len] = '\0';

    // Allocate memory for the time_t array
    time_t *expanded_times = static_cast<time_t*>(malloc(count * sizeof(time_t)));
    if (!expanded_times) {
        free(recurrence_rule);
        return 0;
    }

    // Call the function-under-test
    bool result = icalrecur_expand_recurrence(recurrence_rule, start_time, count, expanded_times);

    // Clean up
    free(recurrence_rule);
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

    LLVMFuzzerTestOneInput_207(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
