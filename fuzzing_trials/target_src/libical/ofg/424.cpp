#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    #include <libical/ical.h>
}

extern "C" int LLVMFuzzerTestOneInput_424(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty and is null-terminated for safe string operations
    if (size == 0) return 0;

    // Allocate memory for a null-terminated string
    char *inputString = new char[size + 1];
    memcpy(inputString, data, size);
    inputString[size] = '\0';

    // Call the function-under-test
    // Use icalparser to parse the input data and create an icalproperty
    icalparser *parser = icalparser_new();
    if (parser != nullptr) {
        icalparser_set_gen_data(parser, inputString);
        
        // Define a line generator function that returns the input string
        auto line_gen_func = [](char *s, size_t size, void *gen_data) -> char* {
            const char* input = static_cast<const char*>(gen_data);
            size_t input_len = strlen(input);
            if (input_len < size) {
                strcpy(s, input);
                return s;
            }
            return nullptr;
        };

        icalcomponent *comp = icalparser_parse(parser, line_gen_func);
        if (comp != nullptr) {
            for (icalproperty *prop = icalcomponent_get_first_property(comp, ICAL_ANY_PROPERTY);
                 prop != nullptr;
                 prop = icalcomponent_get_next_property(comp, ICAL_ANY_PROPERTY)) {
                // Process each property
                icalproperty_kind kind = icalproperty_isa(prop);
                // Normally you would do something with 'kind'
                icalproperty_free(prop); // Free each property after processing
            }
            icalcomponent_free(comp); // Free the component
        }
        icalparser_free(parser); // Free the parser
    }

    // Clean up
    delete[] inputString;

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

    LLVMFuzzerTestOneInput_424(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
