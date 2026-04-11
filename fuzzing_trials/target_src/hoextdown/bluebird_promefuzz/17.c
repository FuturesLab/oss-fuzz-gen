#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "/src/hoextdown/src/buffer.h"
#include "html.h"
#include "document.h"

static void fuzz_hoedown_buffer_put(hoedown_buffer *buffer, const uint8_t *data, size_t size) {
    if (buffer && data && size > 0) {
        hoedown_buffer_put(buffer, data, size);
    }
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create initial buffers
    size_t unit_size = 64;
    hoedown_buffer *buffer1 = hoedown_buffer_new(unit_size);
    hoedown_buffer *buffer2 = hoedown_buffer_new(unit_size);
    hoedown_buffer *buffer3 = hoedown_buffer_new(unit_size);

    if (!buffer1 || !buffer2 || !buffer3) {
        if (buffer1) {
                hoedown_buffer_free(buffer1);
        }
        if (buffer2) {
                hoedown_buffer_free(buffer2);
        }
        if (buffer3) {
                hoedown_buffer_free(buffer3);
        }
        return 0;
    }

    // Append data to buffer1
    fuzz_hoedown_buffer_put(buffer1, Data, Size);

    // Create HTML renderer

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of hoedown_html_renderer_new
    hoedown_renderer *renderer = hoedown_html_renderer_new(HOEDOWN_HTML_HARD_WRAP, 1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (!renderer) {
        hoedown_buffer_free(buffer1);
        hoedown_buffer_free(buffer2);
        hoedown_buffer_free(buffer3);
        return 0;
    }

    // Create document
    hoedown_document *document = hoedown_document_new(renderer, HOEDOWN_EXT_AUTOLINK, 1, 0, NULL, buffer2);
    if (!document) {
        hoedown_html_renderer_free(renderer);
        hoedown_buffer_free(buffer1);
        hoedown_buffer_free(buffer2);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hoedown_buffer_free to hoedown_autolink__www
        uint8_t ret_hoedown_document_ul_item_char_qbhbf = hoedown_document_ul_item_char(NULL);
        if (ret_hoedown_document_ul_item_char_qbhbf < 0){
        	return 0;
        }
        int ret_hoedown_document_is_escaped_vfdgd = hoedown_document_is_escaped(document);
        if (ret_hoedown_document_is_escaped_vfdgd < 0){
        	return 0;
        }
        int ret_hoedown_document_list_depth_ogonq = hoedown_document_list_depth(document);
        if (ret_hoedown_document_list_depth_ogonq < 0){
        	return 0;
        }
        int ret_hoedown_document_list_depth_tclpx = hoedown_document_list_depth(document);
        if (ret_hoedown_document_list_depth_tclpx < 0){
        	return 0;
        }

        size_t ret_hoedown_autolink__www_mmune = hoedown_autolink__www((size_t *)&ret_hoedown_document_ul_item_char_qbhbf, buffer2, (uint8_t *)&ret_hoedown_document_is_escaped_vfdgd, (size_t )ret_hoedown_document_list_depth_ogonq, Size, (unsigned int )ret_hoedown_document_list_depth_tclpx);
        if (ret_hoedown_autolink__www_mmune < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        hoedown_buffer_free(buffer3);
        return 0;
    }

    // Render document
    hoedown_document_render(document, buffer3, Data, Size);

    // Free resources
    hoedown_document_free(document);
    hoedown_html_renderer_free(renderer);
    hoedown_buffer_free(buffer1);
    hoedown_buffer_free(buffer2);
    hoedown_buffer_free(buffer3);

    return 0;
}