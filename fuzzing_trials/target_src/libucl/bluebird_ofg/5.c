#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
  // Ensure size is greater than 0 to have at least one character for the key
  if (size == 0) {
    return 0;
  }

  // Create a UCL object
  ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

  // Use the first part of the data as a key
  char key[256];
  size_t key_len = size < 255 ? size : 255;

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_typed_new to ucl_object_compare_qsort
  const ucl_object_t debtapci;
  memset(&debtapci, 0, sizeof(debtapci));
  ucl_object_t* ret_ucl_object_copy_npzan = ucl_object_copy(&debtapci);
  if (ret_ucl_object_copy_npzan == NULL){
  	return 0;
  }

  int ret_ucl_object_compare_qsort_ddqtn = ucl_object_compare_qsort(&ret_ucl_object_copy_npzan, &obj);
  if (ret_ucl_object_compare_qsort_ddqtn < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  memcpy(key, data, key_len);
  key[key_len] = '\0'; // Ensure null-termination

  // Add a dummy key-value pair to the object
  ucl_object_insert_key(obj, ucl_object_fromstring("dummy_value"), key, key_len, false);

  // Call the function-under-test
  bool result = ucl_object_delete_key(obj, key);

  // Clean up

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_delete_key to ucl_object_emit_full
  struct ucl_emitter_functions* ret_ucl_object_emit_fd_funcs_izwvz = ucl_object_emit_fd_funcs(size);
  if (ret_ucl_object_emit_fd_funcs_izwvz == NULL){
  	return 0;
  }

  bool ret_ucl_object_emit_full_oidxm = ucl_object_emit_full(obj, 0, ret_ucl_object_emit_fd_funcs_izwvz, obj);
  if (ret_ucl_object_emit_full_oidxm == 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  ucl_object_unref(obj);

  return 0;
}