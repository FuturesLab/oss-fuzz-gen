#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1341(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a meaningful string
    if (size == 0) {
        return 0;
    }

    // Create an icalproperty object
    icalproperty *prop = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (prop == NULL) {
        return 0;
    }

    // Allocate memory for the summary string and ensure it's null-terminated
    char *summary = (char *)malloc(size + 1);
    if (summary == NULL) {
        icalproperty_free(prop);
        return 0;
    }
    memcpy(summary, data, size);
    summary[size] = '\0';

    // Call the function-under-test
    icalproperty_set_summary(prop, summary);

    // Retrieve the summary to ensure the function is invoked properly
    const char *retrieved_summary = icalproperty_get_summary(prop);
    if (retrieved_summary) {
        // Perform a simple operation to ensure the summary is not null
        if (strlen(retrieved_summary) > 0) {
            // This confirms that the summary was set and retrieved successfully
            // Add additional operations to increase code coverage
            icalproperty_kind kind = icalproperty_isa(prop);
            if (kind == ICAL_SUMMARY_PROPERTY) {
                // Further operations to ensure the property is correctly identified
            }
        }
    }

    // Clean up
    icalproperty_free(prop);
    free(summary);

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

    LLVMFuzzerTestOneInput_1341(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
