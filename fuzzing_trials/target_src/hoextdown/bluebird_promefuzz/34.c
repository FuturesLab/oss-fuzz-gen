#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "html.h"
#include "document.h"

static void *dummy_realloc_callback(void *ptr, size_t size) {
    return realloc(ptr, size);
}

static void dummy_free_callback(void *ptr) {
    free(ptr);
}

static void dummy_buffer_free_callback(void *buffer) {
    if (buffer) {
        hoedown_buffer *buf = (hoedown_buffer *)buffer;
        if (buf->data_free) {
                buf->data_free(buf->data);
        }
        free(buf);
    }
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    int nesting_level = Data[0] % 5; // arbitrary nesting level choice

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of hoedown_html_toc_renderer_new
    hoedown_renderer *renderer = hoedown_html_toc_renderer_new(-1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    if (!renderer) {
        return 0;
    }

    hoedown_extensions extensions = HOEDOWN_EXT_TABLES | HOEDOWN_EXT_FENCED_CODE;
    size_t max_nesting = (Size > 1) ? Data[1] : 1;
    if (max_nesting == 0) {
        max_nesting = 1;
    }

    hoedown_user_block user_block = NULL;
    
    hoedown_buffer *meta = (hoedown_buffer *)malloc(sizeof(hoedown_buffer));
    if (!meta) {
        free(renderer);
        return 0;
    }
    meta->data = NULL;
    meta->size = 0;
    meta->asize = 0;
    meta->unit = 0;
    meta->data_realloc = dummy_realloc_callback;
    meta->data_free = dummy_free_callback;
    meta->buffer_free = dummy_buffer_free_callback;


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hoedown_document_new

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hoedown_document_new
    hoedown_document *document = hoedown_document_new(renderer, HOEDOWN_EXT_DEFINITION_LISTS, max_nesting, 0, user_block, meta);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR



    if (document) {
        hoedown_buffer *output_buffer = (hoedown_buffer *)malloc(sizeof(hoedown_buffer));
        if (output_buffer) {
            output_buffer->data = (uint8_t *)malloc(Size);
            if (output_buffer->data) {
                output_buffer->size = Size;
                output_buffer->asize = Size;
                output_buffer->unit = 1;
                output_buffer->data_realloc = dummy_realloc_callback;
                output_buffer->data_free = dummy_free_callback;
                output_buffer->buffer_free = dummy_buffer_free_callback;

                hoedown_document_render(document, output_buffer, Data, Size);
                hoedown_document_render_inline(document, output_buffer, Data, Size);

                output_buffer->buffer_free(output_buffer);
            } else {
                free(output_buffer);
            }
        }
        hoedown_document_free(document);
    }

    meta->buffer_free(meta);
    free(renderer);

    return 0;
}