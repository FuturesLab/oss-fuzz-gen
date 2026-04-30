#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
    #include "libical/ical.h"
}

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated for safe string operations
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Attempt to parse the input data as an iCalendar string
    icalcomponent *component = icalparser_parse_string(null_terminated_data);

    // Ensure the component is not NULL
    if (component == NULL) {
        free(null_terminated_data);
        return 0;
    }

    // Call the function-under-test
    const char *relcalid = icalcomponent_get_relcalid(component);

    // Do something with the result to avoid compiler optimizations
    if (relcalid != NULL) {
        // Normally you might log or further process the result
        // Here we'll just use it in a dummy operation
        volatile size_t relcalid_length = strlen(relcalid);
        (void)relcalid_length; // Suppress unused variable warning
    }

    // Clean up

    // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from icalcomponent_get_relcalid to icalcomponent_set_due using the plateau pool
    int day = (int)(data[2] % 31) + 1;
    int year = (int)data[0] + 1900;
    struct icaltimetype due_time = icaltime_from_day_of_year(
        day, year);
    // Ensure dataflow is valid (i.e., non-null)
    if (!component) {
    	return 0;
    }
    icalcomponent_set_due(component, due_time);
    // End mutation: Producer.SPLICE_MUTATOR
    
    icalcomponent_free(component);
    free(null_terminated_data);

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

    LLVMFuzzerTestOneInput_11(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
