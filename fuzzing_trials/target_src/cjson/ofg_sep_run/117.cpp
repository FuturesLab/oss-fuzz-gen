#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_117(const uint8_t* data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_117(const uint8_t* data, size_t size)
{
    cJSON *json;
    cJSON *duplicate;
    size_t offset = 1;
    cJSON_bool recurse;

    if(size <= offset) return 0;
    if(data[size-1] != '\0') return 0;
    if(data[0] != '1' && data[0] != '0') return 0;

    recurse = data[0] == '1' ? 1 : 0;

    json = cJSON_ParseWithOpts((const char*)data + offset, NULL, 1);

    if(json == NULL) return 0;

    duplicate = cJSON_Duplicate(json, recurse);

    if(duplicate != NULL) {
        cJSON_Delete(duplicate);
    }

    cJSON_Delete(json);

    return 0;
}

#ifdef __cplusplus
}
#endif