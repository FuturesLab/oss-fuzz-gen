#include "fuzzer/FuzzedDataProvider.h"
#include <cstdint>
#include <cstddef>
#include <vector>
#include <string>
#include "/src/json-c/linkhash.h" // Correct path for the required header

// Function-under-test
int lh_table_insert(struct lh_table *, const void *, const void *);

// Function to initialize a dummy lh_table
struct lh_table* initialize_lh_table_36() {
  // Properly initialize the lh_table using json-c API
  return lh_kchar_table_new(16, NULL); // Corrected function call with 2 arguments
}

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Create and initialize a dummy lh_table object
  struct lh_table *table = initialize_lh_table_36();
  if (!table) {
    return 0; // Handle initialization failure
  }

  // Consume a random length string for the key and value from the fuzzed data
  std::string key = fuzzed_data.ConsumeRandomLengthString(100);
  std::string value = fuzzed_data.ConsumeRandomLengthString(100);

  // Ensure that key and value are not empty
  if (key.empty() || value.empty()) {
    lh_table_free(table); // Free the table if no valid input
    return 0;
  }

  // Call the function-under-test
  lh_table_insert(table, key.data(), value.data());

  // Cleanup: free the table after use

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from lh_table_insert to json_object_set_userdata
  struct json_object* ret_json_object_new_array_ext_kjhmt = json_object_new_array_ext(-1);
  if (ret_json_object_new_array_ext_kjhmt == NULL){
  	return 0;
  }

  json_object_set_userdata(ret_json_object_new_array_ext_kjhmt, (void *)table, NULL);

  // End mutation: Producer.APPEND_MUTATOR

  lh_table_free(table);

  return 0;
}