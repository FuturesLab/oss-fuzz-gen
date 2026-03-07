#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ucl_parser_new
    struct ucl_parser *parser2 = ucl_parser_new(-1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (parser2 == NULL) {
        ucl_parser_free(parser1);
        return 0;
    }

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of ucl_parser_add_chunk
    ucl_parser_add_chunk(parser2, NULL, size2);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_get_object to ucl_object_pop_keyl
    unsigned char ret_ucl_parser_chunk_peek_jyyle = ucl_parser_chunk_peek(parser2);
    double ret_ucl_object_todouble_frroz = ucl_object_todouble(obj1);
    if (ret_ucl_object_todouble_frroz < 0){
    	return 0;
    }

    ucl_object_t* ret_ucl_object_pop_keyl_bebkm = ucl_object_pop_keyl(obj2, (const char *)&ret_ucl_parser_chunk_peek_jyyle, (size_t )ret_ucl_object_todouble_frroz);
    if (ret_ucl_object_pop_keyl_bebkm == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    ucl_parser_free(parser1);
    ucl_parser_free(parser2);

    return 0;
}