#include <cstdint>  // For uint8_t
#include <cstddef>  // For size_t
#include <cstring>  // For memcpy
#include <cstdlib>  // For malloc and free

extern "C" {
    #include "libical/icalerror.h"
    #include "libical/icalparser.h"
    #include "libical/icalcomponent.h"
}

// Helper function to generate lines from input data
extern "C" char* line_generator_1349(char *s, unsigned long size, void *d) {
    if (size == 0 || d == nullptr) {
        return nullptr;
    }
    
    char **data = static_cast<char**>(d);
    if (*data == nullptr || **data == '\0') {
        return nullptr;
    }

    size_t len = 0;
    while (len < size - 1 && (*data)[len] != '\0' && (*data)[len] != '\n') {
        len++;
    }

    if (len > 0) {
        memcpy(s, *data, len);
        s[len] = '\0';
        *data += len + ((*data)[len] == '\n' ? 1 : 0);
        return s;
    }

    return nullptr;
}

extern "C" int LLVMFuzzerTestOneInput_1349(const uint8_t *data, size_t size) {
    // Initialize the error handling system
    icalerror_clear_errno();

    // Create a null-terminated string from the input data
    char *input = static_cast<char*>(malloc(size + 1));
    if (!input) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input, data, size);
    input[size] = '\0';

    // Parse the input data using libical's parser
    icalparser *parser = icalparser_new();
    if (parser) {
        char buffer[1024];
        char *input_ptr = input;
        icalparser_set_gen_data(parser, &input_ptr);
        icalcomponent *component = icalparser_parse(parser, line_generator_1349);
        if (component) {
            icalcomponent_free(component);
        }
        icalparser_free(parser);
    }

    // Clear any errors that may have been set
    icalerror_clear_errno();

    // Free the allocated memory
    free(input);

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

    LLVMFuzzerTestOneInput_1349(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
