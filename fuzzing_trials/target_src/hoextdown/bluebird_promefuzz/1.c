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

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
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
        
                // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hoedown_buffer_free to hoedown_autolink__email
                int ret_hoedown_document_is_escaped_expfg = hoedown_document_is_escaped(NULL);
                if (ret_hoedown_document_is_escaped_expfg < 0){
                	return 0;
                }
                uint8_t ret_hoedown_document_ul_item_char_sgdyg = hoedown_document_ul_item_char(NULL);
                if (ret_hoedown_document_ul_item_char_sgdyg < 0){
                	return 0;
                }
                uint8_t ret_hoedown_document_hrule_char_hlchu = hoedown_document_hrule_char(NULL);
                if (ret_hoedown_document_hrule_char_hlchu < 0){
                	return 0;
                }
                uint8_t ret_hoedown_document_ul_item_char_ofxiw = hoedown_document_ul_item_char(NULL);
                if (ret_hoedown_document_ul_item_char_ofxiw < 0){
                	return 0;
                }

                size_t ret_hoedown_autolink__email_kzxjj = hoedown_autolink__email((size_t *)&ret_hoedown_document_is_escaped_expfg, buffer3, &ret_hoedown_document_ul_item_char_sgdyg, 64, (size_t )ret_hoedown_document_hrule_char_hlchu, (unsigned int )ret_hoedown_document_ul_item_char_ofxiw);
                if (ret_hoedown_autolink__email_kzxjj < 0){
                	return 0;
                }

                // End mutation: Producer.APPEND_MUTATOR

}
        return 0;
    }

    // Append data to buffer1
    fuzz_hoedown_buffer_put(buffer1, Data, Size);

    // Create HTML renderer
    hoedown_renderer *renderer = hoedown_html_renderer_new(HOEDOWN_HTML_USE_XHTML, 1);
    if (!renderer) {
        hoedown_buffer_free(buffer1);
        hoedown_buffer_free(buffer2);
        hoedown_buffer_free(buffer3);
        return 0;
    }

    // Create document

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of hoedown_document_new
    hoedown_document *document = hoedown_document_new(renderer, HOEDOWN_EXT_AUTOLINK, 64, 0, NULL, buffer2);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (!document) {
        hoedown_html_renderer_free(renderer);
        hoedown_buffer_free(buffer1);
        hoedown_buffer_free(buffer2);
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hoedown_buffer_free with hoedown_buffer_uninit
    hoedown_buffer_uninit(buffer3);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}