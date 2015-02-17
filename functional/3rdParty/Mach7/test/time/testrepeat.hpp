//
//  Mach7: Pattern Matching Library for C++
//
//  Copyright 2011-2013, Texas A&M University.
//  Copyright 2014 Yuriy Solodkyy.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//
//      * Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//
//      * Neither the names of Mach7 project nor the names of its contributors
//        may be used to endorse or promote products derived from this software
//        without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
//  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

///
/// \file
///
/// Definition of yet another repetition macro.
///
/// \author Yuriy Solodkyy <yuriy.solodkyy@gmail.com>
///
/// \see https://parasol.tamu.edu/mach7/
/// \see https://github.com/solodon4/Mach7
/// \see https://github.com/solodon4/SELL
///
/// \note Unlike match.hpp, use of this file does not require member matching
///       definitions or any other definitions.
///
///

#pragma once

#define XTL_TEST_REPEAT_0(m,...)
#define XTL_TEST_REPEAT_1(m,...)                                    m(0,__VA_ARGS__)
#define XTL_TEST_REPEAT_2(m,...)  XTL_TEST_REPEAT_1(m,__VA_ARGS__)  m(1,__VA_ARGS__)
#define XTL_TEST_REPEAT_3(m,...)  XTL_TEST_REPEAT_2(m,__VA_ARGS__)  m(2,__VA_ARGS__)
#define XTL_TEST_REPEAT_4(m,...)  XTL_TEST_REPEAT_3(m,__VA_ARGS__)  m(3,__VA_ARGS__)
#define XTL_TEST_REPEAT_5(m,...)  XTL_TEST_REPEAT_4(m,__VA_ARGS__)  m(4,__VA_ARGS__)
#define XTL_TEST_REPEAT_6(m,...)  XTL_TEST_REPEAT_5(m,__VA_ARGS__)  m(5,__VA_ARGS__)
#define XTL_TEST_REPEAT_7(m,...)  XTL_TEST_REPEAT_6(m,__VA_ARGS__)  m(6,__VA_ARGS__)
#define XTL_TEST_REPEAT_8(m,...)  XTL_TEST_REPEAT_7(m,__VA_ARGS__)  m(7,__VA_ARGS__)
#define XTL_TEST_REPEAT_9(m,...)  XTL_TEST_REPEAT_8(m,__VA_ARGS__)  m(8,__VA_ARGS__)
#define XTL_TEST_REPEAT_10(m,...) XTL_TEST_REPEAT_9(m,__VA_ARGS__)  m(9,__VA_ARGS__)
#define XTL_TEST_REPEAT_11(m,...) XTL_TEST_REPEAT_10(m,__VA_ARGS__) m(10,__VA_ARGS__)
#define XTL_TEST_REPEAT_12(m,...) XTL_TEST_REPEAT_11(m,__VA_ARGS__) m(11,__VA_ARGS__)
#define XTL_TEST_REPEAT_13(m,...) XTL_TEST_REPEAT_12(m,__VA_ARGS__) m(12,__VA_ARGS__)
#define XTL_TEST_REPEAT_14(m,...) XTL_TEST_REPEAT_13(m,__VA_ARGS__) m(13,__VA_ARGS__)
#define XTL_TEST_REPEAT_15(m,...) XTL_TEST_REPEAT_14(m,__VA_ARGS__) m(14,__VA_ARGS__)
#define XTL_TEST_REPEAT_16(m,...) XTL_TEST_REPEAT_15(m,__VA_ARGS__) m(15,__VA_ARGS__)
#define XTL_TEST_REPEAT_17(m,...) XTL_TEST_REPEAT_16(m,__VA_ARGS__) m(16,__VA_ARGS__)
#define XTL_TEST_REPEAT_18(m,...) XTL_TEST_REPEAT_17(m,__VA_ARGS__) m(17,__VA_ARGS__)
#define XTL_TEST_REPEAT_19(m,...) XTL_TEST_REPEAT_18(m,__VA_ARGS__) m(18,__VA_ARGS__)
#define XTL_TEST_REPEAT_20(m,...) XTL_TEST_REPEAT_19(m,__VA_ARGS__) m(19,__VA_ARGS__)
#define XTL_TEST_REPEAT_21(m,...) XTL_TEST_REPEAT_20(m,__VA_ARGS__) m(20,__VA_ARGS__)
#define XTL_TEST_REPEAT_22(m,...) XTL_TEST_REPEAT_21(m,__VA_ARGS__) m(21,__VA_ARGS__)
#define XTL_TEST_REPEAT_23(m,...) XTL_TEST_REPEAT_22(m,__VA_ARGS__) m(22,__VA_ARGS__)
#define XTL_TEST_REPEAT_24(m,...) XTL_TEST_REPEAT_23(m,__VA_ARGS__) m(23,__VA_ARGS__)
#define XTL_TEST_REPEAT_25(m,...) XTL_TEST_REPEAT_24(m,__VA_ARGS__) m(24,__VA_ARGS__)
#define XTL_TEST_REPEAT_26(m,...) XTL_TEST_REPEAT_25(m,__VA_ARGS__) m(25,__VA_ARGS__)
#define XTL_TEST_REPEAT_27(m,...) XTL_TEST_REPEAT_26(m,__VA_ARGS__) m(26,__VA_ARGS__)
#define XTL_TEST_REPEAT_28(m,...) XTL_TEST_REPEAT_27(m,__VA_ARGS__) m(27,__VA_ARGS__)
#define XTL_TEST_REPEAT_29(m,...) XTL_TEST_REPEAT_28(m,__VA_ARGS__) m(28,__VA_ARGS__)
#define XTL_TEST_REPEAT_30(m,...) XTL_TEST_REPEAT_29(m,__VA_ARGS__) m(29,__VA_ARGS__)
#define XTL_TEST_REPEAT_31(m,...) XTL_TEST_REPEAT_30(m,__VA_ARGS__) m(30,__VA_ARGS__)
#define XTL_TEST_REPEAT_32(m,...) XTL_TEST_REPEAT_31(m,__VA_ARGS__) m(31,__VA_ARGS__)
#define XTL_TEST_REPEAT_33(m,...) XTL_TEST_REPEAT_32(m,__VA_ARGS__) m(32,__VA_ARGS__)
#define XTL_TEST_REPEAT_34(m,...) XTL_TEST_REPEAT_33(m,__VA_ARGS__) m(33,__VA_ARGS__)
#define XTL_TEST_REPEAT_35(m,...) XTL_TEST_REPEAT_34(m,__VA_ARGS__) m(34,__VA_ARGS__)
#define XTL_TEST_REPEAT_36(m,...) XTL_TEST_REPEAT_35(m,__VA_ARGS__) m(35,__VA_ARGS__)
#define XTL_TEST_REPEAT_37(m,...) XTL_TEST_REPEAT_36(m,__VA_ARGS__) m(36,__VA_ARGS__)
#define XTL_TEST_REPEAT_38(m,...) XTL_TEST_REPEAT_37(m,__VA_ARGS__) m(37,__VA_ARGS__)
#define XTL_TEST_REPEAT_39(m,...) XTL_TEST_REPEAT_38(m,__VA_ARGS__) m(38,__VA_ARGS__)
#define XTL_TEST_REPEAT_40(m,...) XTL_TEST_REPEAT_39(m,__VA_ARGS__) m(39,__VA_ARGS__)
#define XTL_TEST_REPEAT_41(m,...) XTL_TEST_REPEAT_40(m,__VA_ARGS__) m(40,__VA_ARGS__)
#define XTL_TEST_REPEAT_42(m,...) XTL_TEST_REPEAT_41(m,__VA_ARGS__) m(41,__VA_ARGS__)
#define XTL_TEST_REPEAT_43(m,...) XTL_TEST_REPEAT_42(m,__VA_ARGS__) m(42,__VA_ARGS__)
#define XTL_TEST_REPEAT_44(m,...) XTL_TEST_REPEAT_43(m,__VA_ARGS__) m(43,__VA_ARGS__)
#define XTL_TEST_REPEAT_45(m,...) XTL_TEST_REPEAT_44(m,__VA_ARGS__) m(44,__VA_ARGS__)
#define XTL_TEST_REPEAT_46(m,...) XTL_TEST_REPEAT_45(m,__VA_ARGS__) m(45,__VA_ARGS__)
#define XTL_TEST_REPEAT_47(m,...) XTL_TEST_REPEAT_46(m,__VA_ARGS__) m(46,__VA_ARGS__)
#define XTL_TEST_REPEAT_48(m,...) XTL_TEST_REPEAT_47(m,__VA_ARGS__) m(47,__VA_ARGS__)
#define XTL_TEST_REPEAT_49(m,...) XTL_TEST_REPEAT_48(m,__VA_ARGS__) m(48,__VA_ARGS__)
#define XTL_TEST_REPEAT_50(m,...) XTL_TEST_REPEAT_49(m,__VA_ARGS__) m(49,__VA_ARGS__)
#define XTL_TEST_REPEAT_51(m,...) XTL_TEST_REPEAT_50(m,__VA_ARGS__) m(50,__VA_ARGS__)
#define XTL_TEST_REPEAT_52(m,...) XTL_TEST_REPEAT_51(m,__VA_ARGS__) m(51,__VA_ARGS__)
#define XTL_TEST_REPEAT_53(m,...) XTL_TEST_REPEAT_52(m,__VA_ARGS__) m(52,__VA_ARGS__)
#define XTL_TEST_REPEAT_54(m,...) XTL_TEST_REPEAT_53(m,__VA_ARGS__) m(53,__VA_ARGS__)
#define XTL_TEST_REPEAT_55(m,...) XTL_TEST_REPEAT_54(m,__VA_ARGS__) m(54,__VA_ARGS__)
#define XTL_TEST_REPEAT_56(m,...) XTL_TEST_REPEAT_55(m,__VA_ARGS__) m(55,__VA_ARGS__)
#define XTL_TEST_REPEAT_57(m,...) XTL_TEST_REPEAT_56(m,__VA_ARGS__) m(56,__VA_ARGS__)
#define XTL_TEST_REPEAT_58(m,...) XTL_TEST_REPEAT_57(m,__VA_ARGS__) m(57,__VA_ARGS__)
#define XTL_TEST_REPEAT_59(m,...) XTL_TEST_REPEAT_58(m,__VA_ARGS__) m(58,__VA_ARGS__)
#define XTL_TEST_REPEAT_60(m,...) XTL_TEST_REPEAT_59(m,__VA_ARGS__) m(59,__VA_ARGS__)
#define XTL_TEST_REPEAT_61(m,...) XTL_TEST_REPEAT_60(m,__VA_ARGS__) m(60,__VA_ARGS__)
#define XTL_TEST_REPEAT_62(m,...) XTL_TEST_REPEAT_61(m,__VA_ARGS__) m(61,__VA_ARGS__)
#define XTL_TEST_REPEAT_63(m,...) XTL_TEST_REPEAT_62(m,__VA_ARGS__) m(62,__VA_ARGS__)
#define XTL_TEST_REPEAT_64(m,...) XTL_TEST_REPEAT_63(m,__VA_ARGS__) m(63,__VA_ARGS__)
#define XTL_TEST_REPEAT_65(m,...) XTL_TEST_REPEAT_64(m,__VA_ARGS__) m(64,__VA_ARGS__)
#define XTL_TEST_REPEAT_66(m,...) XTL_TEST_REPEAT_65(m,__VA_ARGS__) m(65,__VA_ARGS__)
#define XTL_TEST_REPEAT_67(m,...) XTL_TEST_REPEAT_66(m,__VA_ARGS__) m(66,__VA_ARGS__)
#define XTL_TEST_REPEAT_68(m,...) XTL_TEST_REPEAT_67(m,__VA_ARGS__) m(67,__VA_ARGS__)
#define XTL_TEST_REPEAT_69(m,...) XTL_TEST_REPEAT_68(m,__VA_ARGS__) m(68,__VA_ARGS__)
#define XTL_TEST_REPEAT_70(m,...) XTL_TEST_REPEAT_69(m,__VA_ARGS__) m(69,__VA_ARGS__)
#define XTL_TEST_REPEAT_71(m,...) XTL_TEST_REPEAT_70(m,__VA_ARGS__) m(70,__VA_ARGS__)
#define XTL_TEST_REPEAT_72(m,...) XTL_TEST_REPEAT_71(m,__VA_ARGS__) m(71,__VA_ARGS__)
#define XTL_TEST_REPEAT_73(m,...) XTL_TEST_REPEAT_72(m,__VA_ARGS__) m(72,__VA_ARGS__)
#define XTL_TEST_REPEAT_74(m,...) XTL_TEST_REPEAT_73(m,__VA_ARGS__) m(73,__VA_ARGS__)
#define XTL_TEST_REPEAT_75(m,...) XTL_TEST_REPEAT_74(m,__VA_ARGS__) m(74,__VA_ARGS__)
#define XTL_TEST_REPEAT_76(m,...) XTL_TEST_REPEAT_75(m,__VA_ARGS__) m(75,__VA_ARGS__)
#define XTL_TEST_REPEAT_77(m,...) XTL_TEST_REPEAT_76(m,__VA_ARGS__) m(76,__VA_ARGS__)
#define XTL_TEST_REPEAT_78(m,...) XTL_TEST_REPEAT_77(m,__VA_ARGS__) m(77,__VA_ARGS__)
#define XTL_TEST_REPEAT_79(m,...) XTL_TEST_REPEAT_78(m,__VA_ARGS__) m(78,__VA_ARGS__)
#define XTL_TEST_REPEAT_80(m,...) XTL_TEST_REPEAT_79(m,__VA_ARGS__) m(79,__VA_ARGS__)
#define XTL_TEST_REPEAT_81(m,...) XTL_TEST_REPEAT_80(m,__VA_ARGS__) m(80,__VA_ARGS__)
#define XTL_TEST_REPEAT_82(m,...) XTL_TEST_REPEAT_81(m,__VA_ARGS__) m(81,__VA_ARGS__)
#define XTL_TEST_REPEAT_83(m,...) XTL_TEST_REPEAT_82(m,__VA_ARGS__) m(82,__VA_ARGS__)
#define XTL_TEST_REPEAT_84(m,...) XTL_TEST_REPEAT_83(m,__VA_ARGS__) m(83,__VA_ARGS__)
#define XTL_TEST_REPEAT_85(m,...) XTL_TEST_REPEAT_84(m,__VA_ARGS__) m(84,__VA_ARGS__)
#define XTL_TEST_REPEAT_86(m,...) XTL_TEST_REPEAT_85(m,__VA_ARGS__) m(85,__VA_ARGS__)
#define XTL_TEST_REPEAT_87(m,...) XTL_TEST_REPEAT_86(m,__VA_ARGS__) m(86,__VA_ARGS__)
#define XTL_TEST_REPEAT_88(m,...) XTL_TEST_REPEAT_87(m,__VA_ARGS__) m(87,__VA_ARGS__)
#define XTL_TEST_REPEAT_89(m,...) XTL_TEST_REPEAT_88(m,__VA_ARGS__) m(88,__VA_ARGS__)
#define XTL_TEST_REPEAT_90(m,...) XTL_TEST_REPEAT_89(m,__VA_ARGS__) m(89,__VA_ARGS__)
#define XTL_TEST_REPEAT_91(m,...) XTL_TEST_REPEAT_90(m,__VA_ARGS__) m(90,__VA_ARGS__)
#define XTL_TEST_REPEAT_92(m,...) XTL_TEST_REPEAT_91(m,__VA_ARGS__) m(91,__VA_ARGS__)
#define XTL_TEST_REPEAT_93(m,...) XTL_TEST_REPEAT_92(m,__VA_ARGS__) m(92,__VA_ARGS__)
#define XTL_TEST_REPEAT_94(m,...) XTL_TEST_REPEAT_93(m,__VA_ARGS__) m(93,__VA_ARGS__)
#define XTL_TEST_REPEAT_95(m,...) XTL_TEST_REPEAT_94(m,__VA_ARGS__) m(94,__VA_ARGS__)
#define XTL_TEST_REPEAT_96(m,...) XTL_TEST_REPEAT_95(m,__VA_ARGS__) m(95,__VA_ARGS__)
#define XTL_TEST_REPEAT_97(m,...) XTL_TEST_REPEAT_96(m,__VA_ARGS__) m(96,__VA_ARGS__)
#define XTL_TEST_REPEAT_98(m,...) XTL_TEST_REPEAT_97(m,__VA_ARGS__) m(97,__VA_ARGS__)
#define XTL_TEST_REPEAT_99(m,...) XTL_TEST_REPEAT_98(m,__VA_ARGS__) m(98,__VA_ARGS__)
#define XTL_TEST_REPEAT_100(m,...) XTL_TEST_REPEAT_99(m,__VA_ARGS__) m(99,__VA_ARGS__)
#define XTL_TEST_REPEAT_101(m,...) XTL_TEST_REPEAT_100(m,__VA_ARGS__) m(100,__VA_ARGS__)
#define XTL_TEST_REPEAT_102(m,...) XTL_TEST_REPEAT_101(m,__VA_ARGS__) m(101,__VA_ARGS__)
#define XTL_TEST_REPEAT_103(m,...) XTL_TEST_REPEAT_102(m,__VA_ARGS__) m(102,__VA_ARGS__)
#define XTL_TEST_REPEAT_104(m,...) XTL_TEST_REPEAT_103(m,__VA_ARGS__) m(103,__VA_ARGS__)
#define XTL_TEST_REPEAT_105(m,...) XTL_TEST_REPEAT_104(m,__VA_ARGS__) m(104,__VA_ARGS__)
#define XTL_TEST_REPEAT_106(m,...) XTL_TEST_REPEAT_105(m,__VA_ARGS__) m(105,__VA_ARGS__)
#define XTL_TEST_REPEAT_107(m,...) XTL_TEST_REPEAT_106(m,__VA_ARGS__) m(106,__VA_ARGS__)
#define XTL_TEST_REPEAT_108(m,...) XTL_TEST_REPEAT_107(m,__VA_ARGS__) m(107,__VA_ARGS__)
#define XTL_TEST_REPEAT_109(m,...) XTL_TEST_REPEAT_108(m,__VA_ARGS__) m(108,__VA_ARGS__)
#define XTL_TEST_REPEAT_110(m,...) XTL_TEST_REPEAT_109(m,__VA_ARGS__) m(109,__VA_ARGS__)
#define XTL_TEST_REPEAT_111(m,...) XTL_TEST_REPEAT_110(m,__VA_ARGS__) m(110,__VA_ARGS__)
#define XTL_TEST_REPEAT_112(m,...) XTL_TEST_REPEAT_111(m,__VA_ARGS__) m(111,__VA_ARGS__)
#define XTL_TEST_REPEAT_113(m,...) XTL_TEST_REPEAT_112(m,__VA_ARGS__) m(112,__VA_ARGS__)
#define XTL_TEST_REPEAT_114(m,...) XTL_TEST_REPEAT_113(m,__VA_ARGS__) m(113,__VA_ARGS__)
#define XTL_TEST_REPEAT_115(m,...) XTL_TEST_REPEAT_114(m,__VA_ARGS__) m(114,__VA_ARGS__)
#define XTL_TEST_REPEAT_116(m,...) XTL_TEST_REPEAT_115(m,__VA_ARGS__) m(115,__VA_ARGS__)
#define XTL_TEST_REPEAT_117(m,...) XTL_TEST_REPEAT_116(m,__VA_ARGS__) m(116,__VA_ARGS__)
#define XTL_TEST_REPEAT_118(m,...) XTL_TEST_REPEAT_117(m,__VA_ARGS__) m(117,__VA_ARGS__)
#define XTL_TEST_REPEAT_119(m,...) XTL_TEST_REPEAT_118(m,__VA_ARGS__) m(118,__VA_ARGS__)
#define XTL_TEST_REPEAT_120(m,...) XTL_TEST_REPEAT_119(m,__VA_ARGS__) m(119,__VA_ARGS__)
#define XTL_TEST_REPEAT_121(m,...) XTL_TEST_REPEAT_120(m,__VA_ARGS__) m(120,__VA_ARGS__)
#define XTL_TEST_REPEAT_122(m,...) XTL_TEST_REPEAT_121(m,__VA_ARGS__) m(121,__VA_ARGS__)
#define XTL_TEST_REPEAT_123(m,...) XTL_TEST_REPEAT_122(m,__VA_ARGS__) m(122,__VA_ARGS__)
#define XTL_TEST_REPEAT_124(m,...) XTL_TEST_REPEAT_123(m,__VA_ARGS__) m(123,__VA_ARGS__)
#define XTL_TEST_REPEAT_125(m,...) XTL_TEST_REPEAT_124(m,__VA_ARGS__) m(124,__VA_ARGS__)

/// Repeats macro m(i) n times with i in [0..n-1]
/// The reason we need this one in addition to XTL_REPEAT and XTL_REPEAT_WITH 
/// is because we want to repeat something that uses XTL_REPEAT and XTL_REPEAT_WITH
/// in its expansion, while macros don't allow recursive expansion.
#define XTL_TEST_REPEAT(n,m,...) XTL_TEST_REPEAT_ ## n(m,__VA_ARGS__)
