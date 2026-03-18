#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for two ucl_object_t objects
    size_t half_size = size / 2;
    const uint8_t *data1 = data;
    size_t size1 = half_size;
    const uint8_t *data2 = data + half_size;
    size_t size2 = size - half_size;

    // Create first UCL object from data1
    struct ucl_parser *parser1 = ucl_parser_new(0);
    if (parser1 == NULL) {
        return 0;
    }
    ucl_parser_add_chunk(parser1, data1, size1);
    const ucl_object_t *obj1 = ucl_parser_get_object(parser1);

    // Create second UCL object from data2
    struct ucl_parser *parser2 = ucl_parser_new(0);
    if (parser2 == NULL) {
        ucl_parser_free(parser1);
        return 0;
    }
    ucl_parser_add_chunk(parser2, data2, size2);
    const ucl_object_t *obj2 = ucl_parser_get_object(parser2);

    // Compare the two UCL objects
    if (obj1 != NULL && obj2 != NULL) {
        int result = ucl_object_compare(obj1, obj2);
    }

    // Clean up
    if (obj1 != NULL) {
        ucl_object_unref(obj1);
    }
    if (obj2 != NULL) {
        ucl_object_unref(obj2);
    }
    ucl_parser_free(parser1);
    ucl_parser_free(parser2);

    return 0;
}