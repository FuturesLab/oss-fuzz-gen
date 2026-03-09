// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_array_replace_index at ucl_util.c:3378:1 in ucl.h
// ucl_array_pop_first at ucl_util.c:3303:1 in ucl.h
// ucl_array_index_of at ucl_util.c:3355:1 in ucl.h
// ucl_array_pop_last at ucl_util.c:3283:1 in ucl.h
// ucl_array_size at ucl_util.c:3323:1 in ucl.h
// ucl_array_find_index at ucl_util.c:3339:1 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

static ucl_object_t* create_random_ucl_object() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj) {
        obj->type = UCL_ARRAY;
        obj->value.av = NULL;
        obj->next = NULL;
        obj->prev = NULL;
        obj->len = 0;
        obj->ref = 1;
    }
    return obj;
}

static void add_random_elements_to_ucl_array(ucl_object_t *array, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        ucl_object_t *element = create_random_ucl_object();
        if (element) {
            element->next = array->value.av;
            array->value.av = element;
            array->len++;
        }
    }
}

int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    ucl_object_t *array = create_random_ucl_object();
    if (!array) return 0;

    add_random_elements_to_ucl_array(array, Size);

    // Fuzz ucl_array_replace_index
    ucl_object_t *new_element = create_random_ucl_object();
    if (new_element) {
        unsigned int index = Data[0] % array->len; // Choose a valid index
        ucl_object_t *replaced = ucl_array_replace_index(array, new_element, index);
        if (replaced) {
            free(replaced);
        }
    }

    // Fuzz ucl_array_pop_first
    ucl_object_t *first_element = ucl_array_pop_first(array);
    if (first_element) {
        free(first_element);
    }

    // Fuzz ucl_array_index_of
    if (new_element) {
        unsigned int index_of_element = ucl_array_index_of(array, new_element);
    }

    // Fuzz ucl_array_pop_last
    ucl_object_t *last_element = ucl_array_pop_last(array);
    if (last_element) {
        free(last_element);
    }

    // Fuzz ucl_array_size
    unsigned int size = ucl_array_size(array);

    // Fuzz ucl_array_find_index
    const ucl_object_t *found_element = ucl_array_find_index(array, Data[0] % (size + 1));

    // Cleanup
    while (array->value.av) {
        ucl_object_t *next = ((ucl_object_t *)array->value.av)->next;
        free(array->value.av);
        array->value.av = next;
    }
    free(array);

    return 0;
}