// This is the entry of 14 fuzz drivers:
// 5, 6, 9, 12, 23, 26, 29, 35, 70, 81, 88, 94, 96, 103
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size);

// Entry function
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    // Driver selector
    if (Size < 1) {
        return 0;
    }
    const uint8_t *selector = Data;
    unsigned int driverIndex = 0;
    memcpy(&driverIndex, selector, 1);

    // Remain data and size
    const uint8_t *remainData = Data + 1;
    size_t remainSize = Size - 1;
    if (remainSize == 0) {
        return 0;
    }

    // Select driver
    switch (driverIndex % 14) {
        case 0:
            return LLVMFuzzerTestOneInput_5(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_6(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_9(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_12(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_23(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_26(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_29(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_35(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_70(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_81(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_88(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_94(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_96(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_103(remainData, remainSize);
        default:
            return 0;
    }
    return 0;
}

int main(int argc, char *argv[])
{
	FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size+1);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);
    data[size] = '\0';

    LLVMFuzzerTestOneInput(data, size);

    free(data);
    fclose(f);
    return 0;
}

