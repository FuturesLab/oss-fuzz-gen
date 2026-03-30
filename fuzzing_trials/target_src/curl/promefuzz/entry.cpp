// This is the entry of 28 fuzz drivers:
// 2, 3, 4, 5, 7, 8, 9, 11, 14, 23, 26, 29, 30, 31, 33, 40, 44, 45, 48, 49, 52, 67,
//  70, 73, 76, 78, 85, 92
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size);

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
    switch (driverIndex % 28) {
        case 0:
            return LLVMFuzzerTestOneInput_2(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_3(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_4(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_5(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_7(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_8(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_9(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_11(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_14(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_23(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_26(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_29(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_30(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_31(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_33(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_40(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_44(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_45(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_48(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_49(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_52(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_67(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_70(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_73(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_76(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_78(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_85(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_92(remainData, remainSize);
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

