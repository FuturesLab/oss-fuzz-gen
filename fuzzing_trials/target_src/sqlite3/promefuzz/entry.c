// This is the entry of 74 fuzz drivers:
// 2, 3, 4, 5, 6, 9, 10, 11, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28
// , 29, 30, 31, 32, 34, 36, 40, 42, 44, 46, 53, 54, 57, 60, 62, 65, 66, 67, 68, 71
// , 75, 76, 78, 80, 81, 85, 86, 87, 90, 94, 96, 98, 99, 101, 102, 105, 111, 112, 1
// 13, 115, 117, 118, 119, 120, 121, 124, 127, 129, 131, 132, 134, 138
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_68(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_112(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_113(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_127(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_132(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_134(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size);

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
    switch (driverIndex % 74) {
        case 0:
            return LLVMFuzzerTestOneInput_2(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_3(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_4(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_5(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_6(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_9(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_10(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_11(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_14(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_15(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_16(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_17(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_18(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_19(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_20(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_21(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_22(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_24(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_25(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_26(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_27(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_28(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_29(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_30(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_31(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_32(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_34(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_36(remainData, remainSize);
        case 28:
            return LLVMFuzzerTestOneInput_40(remainData, remainSize);
        case 29:
            return LLVMFuzzerTestOneInput_42(remainData, remainSize);
        case 30:
            return LLVMFuzzerTestOneInput_44(remainData, remainSize);
        case 31:
            return LLVMFuzzerTestOneInput_46(remainData, remainSize);
        case 32:
            return LLVMFuzzerTestOneInput_53(remainData, remainSize);
        case 33:
            return LLVMFuzzerTestOneInput_54(remainData, remainSize);
        case 34:
            return LLVMFuzzerTestOneInput_57(remainData, remainSize);
        case 35:
            return LLVMFuzzerTestOneInput_60(remainData, remainSize);
        case 36:
            return LLVMFuzzerTestOneInput_62(remainData, remainSize);
        case 37:
            return LLVMFuzzerTestOneInput_65(remainData, remainSize);
        case 38:
            return LLVMFuzzerTestOneInput_66(remainData, remainSize);
        case 39:
            return LLVMFuzzerTestOneInput_67(remainData, remainSize);
        case 40:
            return LLVMFuzzerTestOneInput_68(remainData, remainSize);
        case 41:
            return LLVMFuzzerTestOneInput_71(remainData, remainSize);
        case 42:
            return LLVMFuzzerTestOneInput_75(remainData, remainSize);
        case 43:
            return LLVMFuzzerTestOneInput_76(remainData, remainSize);
        case 44:
            return LLVMFuzzerTestOneInput_78(remainData, remainSize);
        case 45:
            return LLVMFuzzerTestOneInput_80(remainData, remainSize);
        case 46:
            return LLVMFuzzerTestOneInput_81(remainData, remainSize);
        case 47:
            return LLVMFuzzerTestOneInput_85(remainData, remainSize);
        case 48:
            return LLVMFuzzerTestOneInput_86(remainData, remainSize);
        case 49:
            return LLVMFuzzerTestOneInput_87(remainData, remainSize);
        case 50:
            return LLVMFuzzerTestOneInput_90(remainData, remainSize);
        case 51:
            return LLVMFuzzerTestOneInput_94(remainData, remainSize);
        case 52:
            return LLVMFuzzerTestOneInput_96(remainData, remainSize);
        case 53:
            return LLVMFuzzerTestOneInput_98(remainData, remainSize);
        case 54:
            return LLVMFuzzerTestOneInput_99(remainData, remainSize);
        case 55:
            return LLVMFuzzerTestOneInput_101(remainData, remainSize);
        case 56:
            return LLVMFuzzerTestOneInput_102(remainData, remainSize);
        case 57:
            return LLVMFuzzerTestOneInput_105(remainData, remainSize);
        case 58:
            return LLVMFuzzerTestOneInput_111(remainData, remainSize);
        case 59:
            return LLVMFuzzerTestOneInput_112(remainData, remainSize);
        case 60:
            return LLVMFuzzerTestOneInput_113(remainData, remainSize);
        case 61:
            return LLVMFuzzerTestOneInput_115(remainData, remainSize);
        case 62:
            return LLVMFuzzerTestOneInput_117(remainData, remainSize);
        case 63:
            return LLVMFuzzerTestOneInput_118(remainData, remainSize);
        case 64:
            return LLVMFuzzerTestOneInput_119(remainData, remainSize);
        case 65:
            return LLVMFuzzerTestOneInput_120(remainData, remainSize);
        case 66:
            return LLVMFuzzerTestOneInput_121(remainData, remainSize);
        case 67:
            return LLVMFuzzerTestOneInput_124(remainData, remainSize);
        case 68:
            return LLVMFuzzerTestOneInput_127(remainData, remainSize);
        case 69:
            return LLVMFuzzerTestOneInput_129(remainData, remainSize);
        case 70:
            return LLVMFuzzerTestOneInput_131(remainData, remainSize);
        case 71:
            return LLVMFuzzerTestOneInput_132(remainData, remainSize);
        case 72:
            return LLVMFuzzerTestOneInput_134(remainData, remainSize);
        case 73:
            return LLVMFuzzerTestOneInput_138(remainData, remainSize);
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

