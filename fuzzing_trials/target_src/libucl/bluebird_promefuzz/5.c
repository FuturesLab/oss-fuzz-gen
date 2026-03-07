#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static ucl_object_t* create_dummy_ucl_object() {
    ucl_object_t *obj = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    if (obj != NULL) {
        obj->value.ov = ucl_object_new();
        obj->key = "dummy_key";
        obj->keylen = strlen(obj->key);
        obj->type = UCL_OBJECT;
        
        ucl_object_t *child = ucl_object_fromstring("dummy_value");
        ucl_object_insert_key(obj->value.ov, child, "dummy_key", strlen("dummy_key"), false);
    }
    return obj;
}

static void free_ucl_object(ucl_object_t *obj) {
    if (obj != NULL) {
        ucl_object_unref(obj->value.ov);
        free(obj);
    }
}

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    ucl_object_t *root_obj = create_dummy_ucl_object();
    if (root_obj == NULL) {
        return 0;
    }

    const ucl_object_t *lookup_obj1 = ucl_object_lookup(root_obj->value.ov, "dummy_key");
    const ucl_object_t *lookup_obj2 = ucl_object_lookup(root_obj->value.ov, "nonexistent_key");
    const ucl_object_t *lookup_obj3 = ucl_object_lookup(root_obj->value.ov, NULL);

    struct ucl_schema_error err;
    bool is_valid = ucl_object_validate(root_obj->value.ov, lookup_obj1, &err);

    bool bool_value1 = ucl_object_toboolean(lookup_obj1);
    const char *string_value = ucl_object_tostring(lookup_obj1);
    bool bool_value2 = ucl_object_toboolean(lookup_obj2);

    unsigned char *json_output = ucl_object_emit(root_obj->value.ov, UCL_EMIT_JSON);
    unsigned char *config_output = ucl_object_emit(root_obj->value.ov, UCL_EMIT_CONFIG);

    if (json_output != NULL) {
        free(json_output);
    }
    if (config_output != NULL) {
        free(config_output);
    }

    free_ucl_object(root_obj);
    return 0;
}