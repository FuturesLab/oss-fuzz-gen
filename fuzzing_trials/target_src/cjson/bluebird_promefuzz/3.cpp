#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "../cJSON.h"
}

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

static cJSON* createStringArrayFuzz(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return nullptr;
    }
    int count = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    std::vector<const char*> strings;
    for (int i = 0; i < count && Size > 0; ++i) {
        const char* str = reinterpret_cast<const char*>(Data);
        size_t len = strnlen(str, Size);
        if (len < Size) {
            strings.push_back(str);
            Data += len + 1;
            Size -= len + 1;
        } else {
            break;
        }
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cJSON_CreateStringArray
    const char *qolfytfj[1024] = {"qpdel", NULL};
    return cJSON_CreateStringArray(qolfytfj, strings.size());
    // End mutation: Producer.REPLACE_ARG_MUTATOR


}

static cJSON* createIntArrayFuzz(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return nullptr;
    }
    int count = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    if (Size < count * sizeof(int)) {
        return nullptr;
    }
    const int* numbers = reinterpret_cast<const int*>(Data);
    return cJSON_CreateIntArray(numbers, count);
}

static cJSON* createFloatArrayFuzz(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return nullptr;
    }
    int count = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    if (Size < count * sizeof(float)) {
        return nullptr;
    }
    const float* numbers = reinterpret_cast<const float*>(Data);
    return cJSON_CreateFloatArray(numbers, count);
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    cJSON *jsonArray = cJSON_CreateArray();
    if (jsonArray != nullptr) {
        cJSON_Delete(jsonArray);
    }

    jsonArray = createStringArrayFuzz(Data, Size);
    if (jsonArray != nullptr) {
        cJSON_Delete(jsonArray);
    }

    jsonArray = createIntArrayFuzz(Data, Size);
    if (jsonArray != nullptr) {
        cJSON_Delete(jsonArray);
    }

    jsonArray = createFloatArrayFuzz(Data, Size);
    if (jsonArray != nullptr) {
        cJSON_Delete(jsonArray);
    }

    jsonArray = cJSON_CreateArray();
    if (jsonArray != nullptr) {
        cJSON *arrayRef = cJSON_CreateArrayReference(jsonArray);
        if (arrayRef != nullptr) {
            cJSON_Delete(arrayRef);
        }
        cJSON_Delete(jsonArray);
    }

    jsonArray = cJSON_CreateArray();
    if (jsonArray != nullptr) {
        cJSON *item = cJSON_GetArrayItem(jsonArray, 0);
        if (item != nullptr) {
            // Normally do something with item
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_Compare
        cJSON* ret_cJSON_CreateArray_rdgfs = cJSON_CreateArray();
        if (ret_cJSON_CreateArray_rdgfs == NULL){
        	return 0;
        }
        cJSON_bool ret_cJSON_IsArray_iswgd = cJSON_IsArray(NULL);
        if (ret_cJSON_IsArray_iswgd < 0){
        	return 0;
        }

        cJSON_bool ret_cJSON_Compare_oaved = cJSON_Compare(jsonArray, ret_cJSON_CreateArray_rdgfs, ret_cJSON_IsArray_iswgd);
        if (ret_cJSON_Compare_oaved < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        cJSON_Delete(jsonArray);
    }    return 0;
}