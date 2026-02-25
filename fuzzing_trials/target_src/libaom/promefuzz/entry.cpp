// This is the entry of 60 fuzz drivers:
// 1, 4, 5, 6, 9, 10, 11, 12, 13, 14, 16, 18, 19, 20, 23, 24, 25, 27, 28, 29, 30, 3
// 2, 33, 37, 39, 40, 41, 43, 44, 45, 46, 47, 49, 52, 54, 56, 57, 58, 59, 60, 61, 6
// 2, 63, 64, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 81, 82, 83, 84
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size);
extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size);

#ifdef BASELINE_COV
using FuzzFn = int (*)(const uint8_t*, size_t);
static FuzzFn drivers[] = {
    LLVMFuzzerTestOneInput_1,
    LLVMFuzzerTestOneInput_4,
    LLVMFuzzerTestOneInput_5,
    LLVMFuzzerTestOneInput_6,
    LLVMFuzzerTestOneInput_9,
    LLVMFuzzerTestOneInput_10,
    LLVMFuzzerTestOneInput_11,
    LLVMFuzzerTestOneInput_12,
    LLVMFuzzerTestOneInput_13,
    LLVMFuzzerTestOneInput_14,
    LLVMFuzzerTestOneInput_16,
    LLVMFuzzerTestOneInput_18,
    LLVMFuzzerTestOneInput_19,
    LLVMFuzzerTestOneInput_20,
    LLVMFuzzerTestOneInput_23,
    LLVMFuzzerTestOneInput_24,
    LLVMFuzzerTestOneInput_25,
    LLVMFuzzerTestOneInput_27,
    LLVMFuzzerTestOneInput_28,
    LLVMFuzzerTestOneInput_29,
    LLVMFuzzerTestOneInput_30,
    LLVMFuzzerTestOneInput_32,
    LLVMFuzzerTestOneInput_33,
    LLVMFuzzerTestOneInput_37,
    LLVMFuzzerTestOneInput_39,
    LLVMFuzzerTestOneInput_40,
    LLVMFuzzerTestOneInput_41,
    LLVMFuzzerTestOneInput_43,
    LLVMFuzzerTestOneInput_44,
    LLVMFuzzerTestOneInput_45,
    LLVMFuzzerTestOneInput_46,
    LLVMFuzzerTestOneInput_47,
    LLVMFuzzerTestOneInput_49,
    LLVMFuzzerTestOneInput_52,
    LLVMFuzzerTestOneInput_54,
    LLVMFuzzerTestOneInput_56,
    LLVMFuzzerTestOneInput_57,
    LLVMFuzzerTestOneInput_58,
    LLVMFuzzerTestOneInput_59,
    LLVMFuzzerTestOneInput_60,
    LLVMFuzzerTestOneInput_61,
    LLVMFuzzerTestOneInput_62,
    LLVMFuzzerTestOneInput_63,
    LLVMFuzzerTestOneInput_64,
    LLVMFuzzerTestOneInput_68,
    LLVMFuzzerTestOneInput_69,
    LLVMFuzzerTestOneInput_70,
    LLVMFuzzerTestOneInput_71,
    LLVMFuzzerTestOneInput_72,
    LLVMFuzzerTestOneInput_73,
    LLVMFuzzerTestOneInput_74,
    LLVMFuzzerTestOneInput_75,
    LLVMFuzzerTestOneInput_76,
    LLVMFuzzerTestOneInput_77,
    LLVMFuzzerTestOneInput_78,
    LLVMFuzzerTestOneInput_79,
    LLVMFuzzerTestOneInput_81,
    LLVMFuzzerTestOneInput_82,
    LLVMFuzzerTestOneInput_83,
    LLVMFuzzerTestOneInput_84
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const size_t n = sizeof(drivers) / sizeof(drivers[0]);

    for (size_t i = 0; i < n; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            continue;
        } 
        else if (pid == 0) {
            // call driver and _exit with its return value
            int rc = drivers[i](Data, Size);
            exit(0);
        } 
        else {
            int status = 0;
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}

#else
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
    switch (driverIndex % 60) {
        case 0:
            return LLVMFuzzerTestOneInput_1(remainData, remainSize);
        case 1:
            return LLVMFuzzerTestOneInput_4(remainData, remainSize);
        case 2:
            return LLVMFuzzerTestOneInput_5(remainData, remainSize);
        case 3:
            return LLVMFuzzerTestOneInput_6(remainData, remainSize);
        case 4:
            return LLVMFuzzerTestOneInput_9(remainData, remainSize);
        case 5:
            return LLVMFuzzerTestOneInput_10(remainData, remainSize);
        case 6:
            return LLVMFuzzerTestOneInput_11(remainData, remainSize);
        case 7:
            return LLVMFuzzerTestOneInput_12(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_13(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_14(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_16(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_18(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_19(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_20(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_23(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_24(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_25(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_27(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_28(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_29(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_30(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_32(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_33(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_37(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_39(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_40(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_41(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_43(remainData, remainSize);
        case 28:
            return LLVMFuzzerTestOneInput_44(remainData, remainSize);
        case 29:
            return LLVMFuzzerTestOneInput_45(remainData, remainSize);
        case 30:
            return LLVMFuzzerTestOneInput_46(remainData, remainSize);
        case 31:
            return LLVMFuzzerTestOneInput_47(remainData, remainSize);
        case 32:
            return LLVMFuzzerTestOneInput_49(remainData, remainSize);
        case 33:
            return LLVMFuzzerTestOneInput_52(remainData, remainSize);
        case 34:
            return LLVMFuzzerTestOneInput_54(remainData, remainSize);
        case 35:
            return LLVMFuzzerTestOneInput_56(remainData, remainSize);
        case 36:
            return LLVMFuzzerTestOneInput_57(remainData, remainSize);
        case 37:
            return LLVMFuzzerTestOneInput_58(remainData, remainSize);
        case 38:
            return LLVMFuzzerTestOneInput_59(remainData, remainSize);
        case 39:
            return LLVMFuzzerTestOneInput_60(remainData, remainSize);
        case 40:
            return LLVMFuzzerTestOneInput_61(remainData, remainSize);
        case 41:
            return LLVMFuzzerTestOneInput_62(remainData, remainSize);
        case 42:
            return LLVMFuzzerTestOneInput_63(remainData, remainSize);
        case 43:
            return LLVMFuzzerTestOneInput_64(remainData, remainSize);
        case 44:
            return LLVMFuzzerTestOneInput_68(remainData, remainSize);
        case 45:
            return LLVMFuzzerTestOneInput_69(remainData, remainSize);
        case 46:
            return LLVMFuzzerTestOneInput_70(remainData, remainSize);
        case 47:
            return LLVMFuzzerTestOneInput_71(remainData, remainSize);
        case 48:
            return LLVMFuzzerTestOneInput_72(remainData, remainSize);
        case 49:
            return LLVMFuzzerTestOneInput_73(remainData, remainSize);
        case 50:
            return LLVMFuzzerTestOneInput_74(remainData, remainSize);
        case 51:
            return LLVMFuzzerTestOneInput_75(remainData, remainSize);
        case 52:
            return LLVMFuzzerTestOneInput_76(remainData, remainSize);
        case 53:
            return LLVMFuzzerTestOneInput_77(remainData, remainSize);
        case 54:
            return LLVMFuzzerTestOneInput_78(remainData, remainSize);
        case 55:
            return LLVMFuzzerTestOneInput_79(remainData, remainSize);
        case 56:
            return LLVMFuzzerTestOneInput_81(remainData, remainSize);
        case 57:
            return LLVMFuzzerTestOneInput_82(remainData, remainSize);
        case 58:
            return LLVMFuzzerTestOneInput_83(remainData, remainSize);
        case 59:
            return LLVMFuzzerTestOneInput_84(remainData, remainSize);
        default:
            return 0;
    }
    return 0;
}
#endif

#ifdef INC_MAIN
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
#endif

