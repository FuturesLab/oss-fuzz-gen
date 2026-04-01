// This is the entry of 224 fuzz drivers:
// 1, 3, 4, 5, 6, 9, 10, 12, 13, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 29, 31
// , 32, 33, 34, 36, 37, 38, 39, 40, 42, 43, 45, 46, 47, 48, 49, 50, 54, 55, 56, 57
// , 58, 59, 60, 61, 62, 64, 65, 66, 67, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82
// , 84, 85, 86, 87, 89, 92, 93, 94, 96, 98, 99, 101, 102, 103, 104, 105, 106, 107,
//  108, 109, 113, 114, 116, 117, 119, 120, 121, 123, 124, 125, 126, 127, 129, 130,
//  132, 134, 135, 136, 138, 139, 140, 142, 143, 146, 147, 148, 149, 150, 151, 153,
//  155, 156, 157, 158, 159, 162, 163, 164, 165, 169, 170, 171, 172, 175, 176, 177,
//  178, 179, 180, 181, 182, 183, 184, 186, 187, 188, 189, 191, 192, 194, 195, 196,
//  197, 198, 200, 201, 203, 204, 206, 207, 210, 212, 213, 214, 215, 216, 217, 218,
//  219, 220, 221, 222, 224, 225, 229, 230, 231, 232, 233, 234, 235, 237, 242, 243,
//  244, 248, 249, 250, 251, 252, 254, 255, 258, 259, 260, 261, 262, 268, 271, 273,
//  275, 278, 279, 282, 284, 285, 287, 290, 291, 292, 294, 295, 296, 297, 298, 299,
//  300, 302, 303, 304, 310, 312, 313, 315, 317, 318, 319, 320, 322, 325, 326, 327
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <memory.h>

// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions
int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_73(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_107(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_108(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_113(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_114(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_125(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_127(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_130(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_132(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_134(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_135(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_136(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_139(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_142(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_148(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_149(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_150(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_151(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_153(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_155(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_157(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_158(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_159(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_162(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_163(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_164(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_169(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_170(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_171(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_172(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_175(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_176(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_177(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_178(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_179(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_180(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_181(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_182(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_183(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_184(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_186(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_187(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_188(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_189(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_191(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_192(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_194(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_195(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_196(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_197(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_198(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_200(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_201(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_203(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_204(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_206(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_207(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_210(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_212(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_213(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_214(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_215(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_216(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_217(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_218(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_219(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_220(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_221(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_222(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_224(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_225(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_229(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_230(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_231(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_232(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_233(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_234(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_235(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_237(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_242(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_243(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_244(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_248(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_249(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_250(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_251(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_252(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_254(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_255(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_258(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_259(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_260(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_261(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_262(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_268(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_271(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_273(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_275(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_278(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_279(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_282(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_284(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_285(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_287(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_290(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_291(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_292(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_294(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_295(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_296(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_297(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_298(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_299(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_300(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_302(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_303(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_304(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_310(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_312(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_313(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_315(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_317(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_318(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_319(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_320(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_322(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_325(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_326(const uint8_t *Data, size_t Size);
int LLVMFuzzerTestOneInput_327(const uint8_t *Data, size_t Size);

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
    switch (driverIndex % 224) {
        case 0:
            return LLVMFuzzerTestOneInput_1(remainData, remainSize);
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
            return LLVMFuzzerTestOneInput_12(remainData, remainSize);
        case 8:
            return LLVMFuzzerTestOneInput_13(remainData, remainSize);
        case 9:
            return LLVMFuzzerTestOneInput_15(remainData, remainSize);
        case 10:
            return LLVMFuzzerTestOneInput_17(remainData, remainSize);
        case 11:
            return LLVMFuzzerTestOneInput_18(remainData, remainSize);
        case 12:
            return LLVMFuzzerTestOneInput_19(remainData, remainSize);
        case 13:
            return LLVMFuzzerTestOneInput_20(remainData, remainSize);
        case 14:
            return LLVMFuzzerTestOneInput_21(remainData, remainSize);
        case 15:
            return LLVMFuzzerTestOneInput_22(remainData, remainSize);
        case 16:
            return LLVMFuzzerTestOneInput_23(remainData, remainSize);
        case 17:
            return LLVMFuzzerTestOneInput_24(remainData, remainSize);
        case 18:
            return LLVMFuzzerTestOneInput_25(remainData, remainSize);
        case 19:
            return LLVMFuzzerTestOneInput_27(remainData, remainSize);
        case 20:
            return LLVMFuzzerTestOneInput_29(remainData, remainSize);
        case 21:
            return LLVMFuzzerTestOneInput_31(remainData, remainSize);
        case 22:
            return LLVMFuzzerTestOneInput_32(remainData, remainSize);
        case 23:
            return LLVMFuzzerTestOneInput_33(remainData, remainSize);
        case 24:
            return LLVMFuzzerTestOneInput_34(remainData, remainSize);
        case 25:
            return LLVMFuzzerTestOneInput_36(remainData, remainSize);
        case 26:
            return LLVMFuzzerTestOneInput_37(remainData, remainSize);
        case 27:
            return LLVMFuzzerTestOneInput_38(remainData, remainSize);
        case 28:
            return LLVMFuzzerTestOneInput_39(remainData, remainSize);
        case 29:
            return LLVMFuzzerTestOneInput_40(remainData, remainSize);
        case 30:
            return LLVMFuzzerTestOneInput_42(remainData, remainSize);
        case 31:
            return LLVMFuzzerTestOneInput_43(remainData, remainSize);
        case 32:
            return LLVMFuzzerTestOneInput_45(remainData, remainSize);
        case 33:
            return LLVMFuzzerTestOneInput_46(remainData, remainSize);
        case 34:
            return LLVMFuzzerTestOneInput_47(remainData, remainSize);
        case 35:
            return LLVMFuzzerTestOneInput_48(remainData, remainSize);
        case 36:
            return LLVMFuzzerTestOneInput_49(remainData, remainSize);
        case 37:
            return LLVMFuzzerTestOneInput_50(remainData, remainSize);
        case 38:
            return LLVMFuzzerTestOneInput_54(remainData, remainSize);
        case 39:
            return LLVMFuzzerTestOneInput_55(remainData, remainSize);
        case 40:
            return LLVMFuzzerTestOneInput_56(remainData, remainSize);
        case 41:
            return LLVMFuzzerTestOneInput_57(remainData, remainSize);
        case 42:
            return LLVMFuzzerTestOneInput_58(remainData, remainSize);
        case 43:
            return LLVMFuzzerTestOneInput_59(remainData, remainSize);
        case 44:
            return LLVMFuzzerTestOneInput_60(remainData, remainSize);
        case 45:
            return LLVMFuzzerTestOneInput_61(remainData, remainSize);
        case 46:
            return LLVMFuzzerTestOneInput_62(remainData, remainSize);
        case 47:
            return LLVMFuzzerTestOneInput_64(remainData, remainSize);
        case 48:
            return LLVMFuzzerTestOneInput_65(remainData, remainSize);
        case 49:
            return LLVMFuzzerTestOneInput_66(remainData, remainSize);
        case 50:
            return LLVMFuzzerTestOneInput_67(remainData, remainSize);
        case 51:
            return LLVMFuzzerTestOneInput_69(remainData, remainSize);
        case 52:
            return LLVMFuzzerTestOneInput_73(remainData, remainSize);
        case 53:
            return LLVMFuzzerTestOneInput_74(remainData, remainSize);
        case 54:
            return LLVMFuzzerTestOneInput_75(remainData, remainSize);
        case 55:
            return LLVMFuzzerTestOneInput_76(remainData, remainSize);
        case 56:
            return LLVMFuzzerTestOneInput_77(remainData, remainSize);
        case 57:
            return LLVMFuzzerTestOneInput_78(remainData, remainSize);
        case 58:
            return LLVMFuzzerTestOneInput_79(remainData, remainSize);
        case 59:
            return LLVMFuzzerTestOneInput_80(remainData, remainSize);
        case 60:
            return LLVMFuzzerTestOneInput_81(remainData, remainSize);
        case 61:
            return LLVMFuzzerTestOneInput_82(remainData, remainSize);
        case 62:
            return LLVMFuzzerTestOneInput_84(remainData, remainSize);
        case 63:
            return LLVMFuzzerTestOneInput_85(remainData, remainSize);
        case 64:
            return LLVMFuzzerTestOneInput_86(remainData, remainSize);
        case 65:
            return LLVMFuzzerTestOneInput_87(remainData, remainSize);
        case 66:
            return LLVMFuzzerTestOneInput_89(remainData, remainSize);
        case 67:
            return LLVMFuzzerTestOneInput_92(remainData, remainSize);
        case 68:
            return LLVMFuzzerTestOneInput_93(remainData, remainSize);
        case 69:
            return LLVMFuzzerTestOneInput_94(remainData, remainSize);
        case 70:
            return LLVMFuzzerTestOneInput_96(remainData, remainSize);
        case 71:
            return LLVMFuzzerTestOneInput_98(remainData, remainSize);
        case 72:
            return LLVMFuzzerTestOneInput_99(remainData, remainSize);
        case 73:
            return LLVMFuzzerTestOneInput_101(remainData, remainSize);
        case 74:
            return LLVMFuzzerTestOneInput_102(remainData, remainSize);
        case 75:
            return LLVMFuzzerTestOneInput_103(remainData, remainSize);
        case 76:
            return LLVMFuzzerTestOneInput_104(remainData, remainSize);
        case 77:
            return LLVMFuzzerTestOneInput_105(remainData, remainSize);
        case 78:
            return LLVMFuzzerTestOneInput_106(remainData, remainSize);
        case 79:
            return LLVMFuzzerTestOneInput_107(remainData, remainSize);
        case 80:
            return LLVMFuzzerTestOneInput_108(remainData, remainSize);
        case 81:
            return LLVMFuzzerTestOneInput_109(remainData, remainSize);
        case 82:
            return LLVMFuzzerTestOneInput_113(remainData, remainSize);
        case 83:
            return LLVMFuzzerTestOneInput_114(remainData, remainSize);
        case 84:
            return LLVMFuzzerTestOneInput_116(remainData, remainSize);
        case 85:
            return LLVMFuzzerTestOneInput_117(remainData, remainSize);
        case 86:
            return LLVMFuzzerTestOneInput_119(remainData, remainSize);
        case 87:
            return LLVMFuzzerTestOneInput_120(remainData, remainSize);
        case 88:
            return LLVMFuzzerTestOneInput_121(remainData, remainSize);
        case 89:
            return LLVMFuzzerTestOneInput_123(remainData, remainSize);
        case 90:
            return LLVMFuzzerTestOneInput_124(remainData, remainSize);
        case 91:
            return LLVMFuzzerTestOneInput_125(remainData, remainSize);
        case 92:
            return LLVMFuzzerTestOneInput_126(remainData, remainSize);
        case 93:
            return LLVMFuzzerTestOneInput_127(remainData, remainSize);
        case 94:
            return LLVMFuzzerTestOneInput_129(remainData, remainSize);
        case 95:
            return LLVMFuzzerTestOneInput_130(remainData, remainSize);
        case 96:
            return LLVMFuzzerTestOneInput_132(remainData, remainSize);
        case 97:
            return LLVMFuzzerTestOneInput_134(remainData, remainSize);
        case 98:
            return LLVMFuzzerTestOneInput_135(remainData, remainSize);
        case 99:
            return LLVMFuzzerTestOneInput_136(remainData, remainSize);
        case 100:
            return LLVMFuzzerTestOneInput_138(remainData, remainSize);
        case 101:
            return LLVMFuzzerTestOneInput_139(remainData, remainSize);
        case 102:
            return LLVMFuzzerTestOneInput_140(remainData, remainSize);
        case 103:
            return LLVMFuzzerTestOneInput_142(remainData, remainSize);
        case 104:
            return LLVMFuzzerTestOneInput_143(remainData, remainSize);
        case 105:
            return LLVMFuzzerTestOneInput_146(remainData, remainSize);
        case 106:
            return LLVMFuzzerTestOneInput_147(remainData, remainSize);
        case 107:
            return LLVMFuzzerTestOneInput_148(remainData, remainSize);
        case 108:
            return LLVMFuzzerTestOneInput_149(remainData, remainSize);
        case 109:
            return LLVMFuzzerTestOneInput_150(remainData, remainSize);
        case 110:
            return LLVMFuzzerTestOneInput_151(remainData, remainSize);
        case 111:
            return LLVMFuzzerTestOneInput_153(remainData, remainSize);
        case 112:
            return LLVMFuzzerTestOneInput_155(remainData, remainSize);
        case 113:
            return LLVMFuzzerTestOneInput_156(remainData, remainSize);
        case 114:
            return LLVMFuzzerTestOneInput_157(remainData, remainSize);
        case 115:
            return LLVMFuzzerTestOneInput_158(remainData, remainSize);
        case 116:
            return LLVMFuzzerTestOneInput_159(remainData, remainSize);
        case 117:
            return LLVMFuzzerTestOneInput_162(remainData, remainSize);
        case 118:
            return LLVMFuzzerTestOneInput_163(remainData, remainSize);
        case 119:
            return LLVMFuzzerTestOneInput_164(remainData, remainSize);
        case 120:
            return LLVMFuzzerTestOneInput_165(remainData, remainSize);
        case 121:
            return LLVMFuzzerTestOneInput_169(remainData, remainSize);
        case 122:
            return LLVMFuzzerTestOneInput_170(remainData, remainSize);
        case 123:
            return LLVMFuzzerTestOneInput_171(remainData, remainSize);
        case 124:
            return LLVMFuzzerTestOneInput_172(remainData, remainSize);
        case 125:
            return LLVMFuzzerTestOneInput_175(remainData, remainSize);
        case 126:
            return LLVMFuzzerTestOneInput_176(remainData, remainSize);
        case 127:
            return LLVMFuzzerTestOneInput_177(remainData, remainSize);
        case 128:
            return LLVMFuzzerTestOneInput_178(remainData, remainSize);
        case 129:
            return LLVMFuzzerTestOneInput_179(remainData, remainSize);
        case 130:
            return LLVMFuzzerTestOneInput_180(remainData, remainSize);
        case 131:
            return LLVMFuzzerTestOneInput_181(remainData, remainSize);
        case 132:
            return LLVMFuzzerTestOneInput_182(remainData, remainSize);
        case 133:
            return LLVMFuzzerTestOneInput_183(remainData, remainSize);
        case 134:
            return LLVMFuzzerTestOneInput_184(remainData, remainSize);
        case 135:
            return LLVMFuzzerTestOneInput_186(remainData, remainSize);
        case 136:
            return LLVMFuzzerTestOneInput_187(remainData, remainSize);
        case 137:
            return LLVMFuzzerTestOneInput_188(remainData, remainSize);
        case 138:
            return LLVMFuzzerTestOneInput_189(remainData, remainSize);
        case 139:
            return LLVMFuzzerTestOneInput_191(remainData, remainSize);
        case 140:
            return LLVMFuzzerTestOneInput_192(remainData, remainSize);
        case 141:
            return LLVMFuzzerTestOneInput_194(remainData, remainSize);
        case 142:
            return LLVMFuzzerTestOneInput_195(remainData, remainSize);
        case 143:
            return LLVMFuzzerTestOneInput_196(remainData, remainSize);
        case 144:
            return LLVMFuzzerTestOneInput_197(remainData, remainSize);
        case 145:
            return LLVMFuzzerTestOneInput_198(remainData, remainSize);
        case 146:
            return LLVMFuzzerTestOneInput_200(remainData, remainSize);
        case 147:
            return LLVMFuzzerTestOneInput_201(remainData, remainSize);
        case 148:
            return LLVMFuzzerTestOneInput_203(remainData, remainSize);
        case 149:
            return LLVMFuzzerTestOneInput_204(remainData, remainSize);
        case 150:
            return LLVMFuzzerTestOneInput_206(remainData, remainSize);
        case 151:
            return LLVMFuzzerTestOneInput_207(remainData, remainSize);
        case 152:
            return LLVMFuzzerTestOneInput_210(remainData, remainSize);
        case 153:
            return LLVMFuzzerTestOneInput_212(remainData, remainSize);
        case 154:
            return LLVMFuzzerTestOneInput_213(remainData, remainSize);
        case 155:
            return LLVMFuzzerTestOneInput_214(remainData, remainSize);
        case 156:
            return LLVMFuzzerTestOneInput_215(remainData, remainSize);
        case 157:
            return LLVMFuzzerTestOneInput_216(remainData, remainSize);
        case 158:
            return LLVMFuzzerTestOneInput_217(remainData, remainSize);
        case 159:
            return LLVMFuzzerTestOneInput_218(remainData, remainSize);
        case 160:
            return LLVMFuzzerTestOneInput_219(remainData, remainSize);
        case 161:
            return LLVMFuzzerTestOneInput_220(remainData, remainSize);
        case 162:
            return LLVMFuzzerTestOneInput_221(remainData, remainSize);
        case 163:
            return LLVMFuzzerTestOneInput_222(remainData, remainSize);
        case 164:
            return LLVMFuzzerTestOneInput_224(remainData, remainSize);
        case 165:
            return LLVMFuzzerTestOneInput_225(remainData, remainSize);
        case 166:
            return LLVMFuzzerTestOneInput_229(remainData, remainSize);
        case 167:
            return LLVMFuzzerTestOneInput_230(remainData, remainSize);
        case 168:
            return LLVMFuzzerTestOneInput_231(remainData, remainSize);
        case 169:
            return LLVMFuzzerTestOneInput_232(remainData, remainSize);
        case 170:
            return LLVMFuzzerTestOneInput_233(remainData, remainSize);
        case 171:
            return LLVMFuzzerTestOneInput_234(remainData, remainSize);
        case 172:
            return LLVMFuzzerTestOneInput_235(remainData, remainSize);
        case 173:
            return LLVMFuzzerTestOneInput_237(remainData, remainSize);
        case 174:
            return LLVMFuzzerTestOneInput_242(remainData, remainSize);
        case 175:
            return LLVMFuzzerTestOneInput_243(remainData, remainSize);
        case 176:
            return LLVMFuzzerTestOneInput_244(remainData, remainSize);
        case 177:
            return LLVMFuzzerTestOneInput_248(remainData, remainSize);
        case 178:
            return LLVMFuzzerTestOneInput_249(remainData, remainSize);
        case 179:
            return LLVMFuzzerTestOneInput_250(remainData, remainSize);
        case 180:
            return LLVMFuzzerTestOneInput_251(remainData, remainSize);
        case 181:
            return LLVMFuzzerTestOneInput_252(remainData, remainSize);
        case 182:
            return LLVMFuzzerTestOneInput_254(remainData, remainSize);
        case 183:
            return LLVMFuzzerTestOneInput_255(remainData, remainSize);
        case 184:
            return LLVMFuzzerTestOneInput_258(remainData, remainSize);
        case 185:
            return LLVMFuzzerTestOneInput_259(remainData, remainSize);
        case 186:
            return LLVMFuzzerTestOneInput_260(remainData, remainSize);
        case 187:
            return LLVMFuzzerTestOneInput_261(remainData, remainSize);
        case 188:
            return LLVMFuzzerTestOneInput_262(remainData, remainSize);
        case 189:
            return LLVMFuzzerTestOneInput_268(remainData, remainSize);
        case 190:
            return LLVMFuzzerTestOneInput_271(remainData, remainSize);
        case 191:
            return LLVMFuzzerTestOneInput_273(remainData, remainSize);
        case 192:
            return LLVMFuzzerTestOneInput_275(remainData, remainSize);
        case 193:
            return LLVMFuzzerTestOneInput_278(remainData, remainSize);
        case 194:
            return LLVMFuzzerTestOneInput_279(remainData, remainSize);
        case 195:
            return LLVMFuzzerTestOneInput_282(remainData, remainSize);
        case 196:
            return LLVMFuzzerTestOneInput_284(remainData, remainSize);
        case 197:
            return LLVMFuzzerTestOneInput_285(remainData, remainSize);
        case 198:
            return LLVMFuzzerTestOneInput_287(remainData, remainSize);
        case 199:
            return LLVMFuzzerTestOneInput_290(remainData, remainSize);
        case 200:
            return LLVMFuzzerTestOneInput_291(remainData, remainSize);
        case 201:
            return LLVMFuzzerTestOneInput_292(remainData, remainSize);
        case 202:
            return LLVMFuzzerTestOneInput_294(remainData, remainSize);
        case 203:
            return LLVMFuzzerTestOneInput_295(remainData, remainSize);
        case 204:
            return LLVMFuzzerTestOneInput_296(remainData, remainSize);
        case 205:
            return LLVMFuzzerTestOneInput_297(remainData, remainSize);
        case 206:
            return LLVMFuzzerTestOneInput_298(remainData, remainSize);
        case 207:
            return LLVMFuzzerTestOneInput_299(remainData, remainSize);
        case 208:
            return LLVMFuzzerTestOneInput_300(remainData, remainSize);
        case 209:
            return LLVMFuzzerTestOneInput_302(remainData, remainSize);
        case 210:
            return LLVMFuzzerTestOneInput_303(remainData, remainSize);
        case 211:
            return LLVMFuzzerTestOneInput_304(remainData, remainSize);
        case 212:
            return LLVMFuzzerTestOneInput_310(remainData, remainSize);
        case 213:
            return LLVMFuzzerTestOneInput_312(remainData, remainSize);
        case 214:
            return LLVMFuzzerTestOneInput_313(remainData, remainSize);
        case 215:
            return LLVMFuzzerTestOneInput_315(remainData, remainSize);
        case 216:
            return LLVMFuzzerTestOneInput_317(remainData, remainSize);
        case 217:
            return LLVMFuzzerTestOneInput_318(remainData, remainSize);
        case 218:
            return LLVMFuzzerTestOneInput_319(remainData, remainSize);
        case 219:
            return LLVMFuzzerTestOneInput_320(remainData, remainSize);
        case 220:
            return LLVMFuzzerTestOneInput_322(remainData, remainSize);
        case 221:
            return LLVMFuzzerTestOneInput_325(remainData, remainSize);
        case 222:
            return LLVMFuzzerTestOneInput_326(remainData, remainSize);
        case 223:
            return LLVMFuzzerTestOneInput_327(remainData, remainSize);
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

