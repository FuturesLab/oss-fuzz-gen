#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstring>

extern "C" int json_parse_int64(const char *, int64_t *);

extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Consume a string from the input data
  std::string json_string = fuzzed_data.ConsumeBytesAsString(fuzzed_data.remaining_bytes());

  // Prepare an int64_t variable to hold the parsed result
  int64_t parsed_value = 0;

  // Call the function-under-test
  json_parse_int64(json_string.c_str(), &parsed_value);

  return 0;
}