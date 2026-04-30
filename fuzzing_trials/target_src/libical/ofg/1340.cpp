#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_1340(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a null-terminated string
    if (size < 1) {
        return 0;
    }

    // Initialize a dummy icalproperty object
    icalproperty *property = icalproperty_new(ICAL_SUMMARY_PROPERTY);
    if (property == NULL) {
        return 0;
    }

    // Allocate memory for a null-terminated string
    char *summary = (char *)malloc(size + 1);
    if (summary == NULL) {
        icalproperty_free(property);
        return 0;
    }

    // Copy the data into the summary string and null-terminate it
    memcpy(summary, data, size);
    summary[size] = '\0';

    // Ensure that the summary is not empty to maximize function utilization
    if (strlen(summary) == 0) {
        free(summary);
        icalproperty_free(property);
        return 0;
    }

    // Call the function-under-test
    icalproperty_set_summary(property, summary);

    // Verify the summary was set correctly
    const char *retrieved_summary = icalproperty_get_summary(property);
    if (retrieved_summary != NULL && strcmp(retrieved_summary, summary) != 0) {
        // Handle unexpected behavior
    }

    // Clean up
    free(summary);
    icalproperty_free(property);

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

    LLVMFuzzerTestOneInput_1340(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
