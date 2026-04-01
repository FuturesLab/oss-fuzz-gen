#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

// Include the correct headers for json-c functions
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
  // Initialize FuzzedDataProvider with the input data
  FuzzedDataProvider fuzzed_data(data, size);

  // Consume a random length string from the fuzzed data
  std::string json_string = fuzzed_data.ConsumeRandomLengthString();

  // Parse the JSON string to create a json_object
  struct json_object *json_obj = json_tokener_parse(json_string.c_str());

  // Check if the json_obj is not null and is an array
  if (json_obj != nullptr && json_object_get_type(json_obj) == json_type_array) {
    // Call the function-under-test
    size_t length = json_object_array_length(json_obj);
  }

  // Free the JSON object
  if (json_obj != nullptr) {
    json_object_put(json_obj);
  }

  return 0;
}