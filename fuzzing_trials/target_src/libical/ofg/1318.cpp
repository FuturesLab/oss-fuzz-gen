#include <libical/ical.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_1318(const uint8_t *data, size_t size) {
    // Ensure the data is not empty to provide meaningful input
    if (size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated to safely convert to a string
    char *queryname = new char[size + 1];
    if (queryname == nullptr) {
        return 0;
    }

    memcpy(queryname, data, size);
    queryname[size] = '\0';

    // Call the function-under-test
    icalproperty *property = icalproperty_new_queryname(queryname);

    // Check if the property was successfully created and perform operations
    if (property != nullptr) {
        // Example operation: retrieve and print the query name
        const char *retrieved_queryname = icalproperty_get_queryname(property);
        if (retrieved_queryname != nullptr) {
            printf("Query name: %s\n", retrieved_queryname);
        }
        icalproperty_free(property);
    }

    delete[] queryname;

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

    LLVMFuzzerTestOneInput_1318(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
