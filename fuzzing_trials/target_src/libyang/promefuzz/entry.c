// This is the entry of 37 fuzz drivers:
// 2, 5, 9, 11, 17, 20, 21, 22, 25, 26, 30, 32, 33, 38, 52, 53, 57, 64, 65, 66, 67,
//  70, 72, 73, 74, 79, 81, 86, 87, 91, 95, 98, 101, 105, 111, 114, 120
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_95(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_114(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size);

// Entry function
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
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
    switch (driverIndex % 37) {
        case 0:
            return LLVMFuzzerTestOneInput_2(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_5(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_9(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_11(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_17(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_20(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_21(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_22(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_25(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_26(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_30(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_32(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_33(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_38(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_52(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_53(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_57(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_64(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_65(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_66(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_67(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_70(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_72(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_73(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_74(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_79(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_81(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_86(remainData, remainSize);
        case 28:
            return LLVMFuzzerTestOneInput_87(remainData, remainSize);
        case 29:
            return LLVMFuzzerTestOneInput_91(remainData, remainSize);
        case 30:
            return LLVMFuzzerTestOneInput_95(remainData, remainSize);
        case 31:
            return LLVMFuzzerTestOneInput_98(remainData, remainSize);
        case 32:
            return LLVMFuzzerTestOneInput_101(remainData, remainSize);
        case 33:
            return LLVMFuzzerTestOneInput_105(remainData, remainSize);
        case 34:
            return LLVMFuzzerTestOneInput_111(remainData, remainSize);
        case 35:
            return LLVMFuzzerTestOneInput_114(remainData, remainSize);
        case 36:
            return LLVMFuzzerTestOneInput_120(remainData, remainSize);
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

