// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_unmarshal_abstract_threaded at marsh.c:1287:7 in janet.h
// janet_unmarshal_ensure at marsh.c:1221:6 in janet.h
// janet_unmarshal_abstract_reuse at marsh.c:1272:6 in janet.h
// janet_marshal_ptr at marsh.c:391:6 in janet.h
// janet_marshal_abstract at marsh.c:430:6 in janet.h
// janet_marshal_size at marsh.c:376:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static JanetMarshalContext *create_context(const uint8_t *Data, size_t Size) {
    JanetMarshalContext *ctx = (JanetMarshalContext *)malloc(sizeof(JanetMarshalContext));
    if (!ctx) return NULL;
    // Initialize context with data
    // Assuming there are functions to initialize the context, e.g., janet_marshal_context_init
    // janet_marshal_context_init(ctx, Data, Size);
    return ctx;
}

static void destroy_context(JanetMarshalContext *ctx) {
    // Assuming there's a function to clean up the context, e.g., janet_marshal_context_deinit
    // janet_marshal_context_deinit(ctx);
    free(ctx);
}

static size_t read_size_t(const uint8_t *Data, size_t Size, size_t *index) {
    size_t value = 0;
    if (*index + sizeof(size_t) <= Size) {
        memcpy(&value, Data + *index, sizeof(size_t));
        *index += sizeof(size_t);
    }
    return value;
}

static void *read_pointer(const uint8_t *Data, size_t Size, size_t *index) {
    void *ptr = NULL;
    if (*index + sizeof(void *) <= Size) {
        memcpy(&ptr, Data + *index, sizeof(void *));
        *index += sizeof(void *);
    }
    return ptr;
}

int LLVMFuzzerTestOneInput_201(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    JanetMarshalContext *ctx = create_context(Data, Size);
    if (!ctx) return 0;

    size_t index = 0;
    while (index < Size) {
        switch (Data[index] % 6) {
            case 0: {
                size_t size = read_size_t(Data, Size, &index);
                janet_unmarshal_abstract_threaded(ctx, size);
                break;
            }
            case 1: {
                size_t size = read_size_t(Data, Size, &index);
                janet_unmarshal_ensure(ctx, size);
                break;
            }
            case 2: {
                void *p = read_pointer(Data, Size, &index);
                if (p != NULL) {
                    janet_unmarshal_abstract_reuse(ctx, p);
                }
                break;
            }
            case 3: {
                const void *value = read_pointer(Data, Size, &index);
                if (value != NULL) {
                    janet_marshal_ptr(ctx, value);
                }
                break;
            }
            case 4: {
                JanetAbstract abstract = read_pointer(Data, Size, &index);
                if (abstract != NULL) {
                    janet_marshal_abstract(ctx, abstract);
                }
                break;
            }
            case 5: {
                size_t value = read_size_t(Data, Size, &index);
                janet_marshal_size(ctx, value);
                break;
            }
            default:
                break;
        }
    }

    destroy_context(ctx);
    return 0;
}