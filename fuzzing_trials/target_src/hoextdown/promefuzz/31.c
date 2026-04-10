// This fuzz driver is generated for library hoextdown, aiming to fuzz the following functions:
// hoedown_document_new at document.c:3979:1 in document.h
// hoedown_document_list_depth at document.c:4309:1 in document.h
// hoedown_html_is_tag at html.c:24:1 in html.h
// hoedown_document_footnote_id at document.c:4303:1 in document.h
// hoedown_document_free at document.c:4246:1 in document.h
// hoedown_stack_uninit at stack.c:24:1 in stack.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "html.h"
#include "document.h"

static hoedown_renderer dummy_renderer;
static hoedown_buffer dummy_buffer;
static hoedown_stack dummy_stack;

static void initialize_dummy_renderer() {
    memset(&dummy_renderer, 0, sizeof(dummy_renderer));
}

static void initialize_dummy_buffer() {
    memset(&dummy_buffer, 0, sizeof(dummy_buffer));
}

static void initialize_dummy_stack() {
    memset(&dummy_stack, 0, sizeof(dummy_stack));
}

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    initialize_dummy_renderer();
    initialize_dummy_buffer();
    initialize_dummy_stack();

    hoedown_extensions extensions = (hoedown_extensions)(Data[0] % 22);
    size_t max_nesting = (Size > 1) ? Data[1] : 1;
    if (max_nesting == 0) max_nesting = 1;
    uint8_t attr_activation = (Size > 2) ? Data[2] : 0;
    hoedown_user_block user_block = NULL;

    hoedown_document *document = hoedown_document_new(
        &dummy_renderer,
        extensions,
        max_nesting,
        attr_activation,
        user_block,
        &dummy_buffer
    );

    if (document) {
        // Fuzz hoedown_document_list_depth
        int list_depth = hoedown_document_list_depth(document);

        // Fuzz hoedown_html_is_tag
        if (Size > 3) {
            hoedown_html_tag tag_type = hoedown_html_is_tag(Data + 3, Size - 3, "div");
        }

        // Fuzz hoedown_document_footnote_id
        const hoedown_buffer *footnote_id = hoedown_document_footnote_id(document);

        // Clean up
        hoedown_document_free(document);
    }

    // Fuzz hoedown_stack_uninit
    hoedown_stack_uninit(&dummy_stack);

    return 0;
}