#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
  // Initialize FuzzedDataProvider with the input data
  FuzzedDataProvider fuzzed_data(data, size);

  // Create a JSON object
  json_object *jobj = json_object_new_object();
  if (jobj == nullptr) {
    return 0; // If creation fails, exit early
  }

  // Create a JSON array and add it to the JSON object
  json_object *jarray = json_object_new_array();
  if (jarray == nullptr) {
    json_object_put(jobj);
    return 0; // If creation fails, clean up and exit early
  }
  json_object_object_add(jobj, "array", jarray);

  // Populate the array with some elements
  for (size_t i = 0; i < 10; ++i) {
    json_object_array_add(jarray, json_object_new_int(static_cast<int>(i)));
  }

  // Consume two size_t values for index and count
  size_t idx = fuzzed_data.ConsumeIntegralInRange<size_t>(0, 9);
  size_t count = fuzzed_data.ConsumeIntegralInRange<size_t>(0, 10 - idx);

  // Call the function-under-test
  json_object_array_del_idx(jarray, idx, count);

  // Clean up
  json_object_put(jobj);

  return 0;
}