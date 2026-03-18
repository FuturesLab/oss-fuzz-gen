// This is the entry of 52 fuzz drivers:
// 1, 3, 8, 11, 12, 15, 16, 19, 20, 21, 23, 24, 26, 30, 34, 36, 37, 38, 39, 41, 42,
//  43, 44, 45, 46, 47, 49, 54, 59, 64, 66, 70, 74, 75, 77, 78, 80, 82, 83, 84, 85,
//  86, 87, 90, 94, 97, 98, 106, 111, 117, 118, 119
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size);

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
    switch (driverIndex % 52) {
        case 0:
            return LLVMFuzzerTestOneInput_1(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_3(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_8(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_11(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_12(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_15(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_16(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_19(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_20(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_21(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_23(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_24(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_26(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_30(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_34(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_36(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_37(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_38(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_39(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_41(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_42(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_43(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_44(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_45(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_46(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_47(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_49(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_54(remainData, remainSize);
        case 28:
            return LLVMFuzzerTestOneInput_59(remainData, remainSize);
        case 29:
            return LLVMFuzzerTestOneInput_64(remainData, remainSize);
        case 30:
            return LLVMFuzzerTestOneInput_66(remainData, remainSize);
        case 31:
            return LLVMFuzzerTestOneInput_70(remainData, remainSize);
        case 32:
            return LLVMFuzzerTestOneInput_74(remainData, remainSize);
        case 33:
            return LLVMFuzzerTestOneInput_75(remainData, remainSize);
        case 34:
            return LLVMFuzzerTestOneInput_77(remainData, remainSize);
        case 35:
            return LLVMFuzzerTestOneInput_78(remainData, remainSize);
        case 36:
            return LLVMFuzzerTestOneInput_80(remainData, remainSize);
        case 37:
            return LLVMFuzzerTestOneInput_82(remainData, remainSize);
        case 38:
            return LLVMFuzzerTestOneInput_83(remainData, remainSize);
        case 39:
            return LLVMFuzzerTestOneInput_84(remainData, remainSize);
        case 40:
            return LLVMFuzzerTestOneInput_85(remainData, remainSize);
        case 41:
            return LLVMFuzzerTestOneInput_86(remainData, remainSize);
        case 42:
            return LLVMFuzzerTestOneInput_87(remainData, remainSize);
        case 43:
            return LLVMFuzzerTestOneInput_90(remainData, remainSize);
        case 44:
            return LLVMFuzzerTestOneInput_94(remainData, remainSize);
        case 45:
            return LLVMFuzzerTestOneInput_97(remainData, remainSize);
        case 46:
            return LLVMFuzzerTestOneInput_98(remainData, remainSize);
        case 47:
            return LLVMFuzzerTestOneInput_106(remainData, remainSize);
        case 48:
            return LLVMFuzzerTestOneInput_111(remainData, remainSize);
        case 49:
            return LLVMFuzzerTestOneInput_117(remainData, remainSize);
        case 50:
            return LLVMFuzzerTestOneInput_118(remainData, remainSize);
        case 51:
            return LLVMFuzzerTestOneInput_119(remainData, remainSize);
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

