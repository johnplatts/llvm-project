// REQUIRES: arm-registered-target,x86-registered-target

// RUN: %clang_cc1 -triple thumbv7-windows -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-COFF
// RUN: %clang_cc1 -triple i686-windows -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-COFF
// RUN: %clang_cc1 -triple x86_64-windows -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-COFF

// RUN: %clang_cc1 -triple armv7-elf -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-ELF -check-prefix CHECK-ELF32
// RUN: %clang_cc1 -triple i686-elf -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-ELF -check-prefix CHECK-ELF32
// RUN: %clang_cc1 -triple x86_64-elf -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-ELF -check-prefix CHECK-ELF64

// RUN: %clang_cc1 -triple armv7-macho -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-MACHO -check-prefix CHECK-MACHO32
// RUN: %clang_cc1 -triple i386-apple-macosx -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-MACHO -check-prefix CHECK-MACHO32
// RUN: %clang_cc1 -triple x86_64-macho -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-MACHO -check-prefix CHECK-MACHO64

// RUN: %clang_cc1 -triple thumbv7-windows -S %s -o - | FileCheck %s -check-prefix CHECK-ASM-COFF
// RUN: %clang_cc1 -triple thumbv7-elf -S %s -o - | FileCheck %s -check-prefix CHECK-ASM-ELF
// RUN: %clang_cc1 -triple thumbv7-macho -S %s -o - | FileCheck %s -check-prefix CHECK-ASM-MACHO

typedef struct __CFString *CFStringRef;
const CFStringRef one = (CFStringRef)__builtin___CFStringMakeConstantString("one");
const CFStringRef two = (CFStringRef)__builtin___CFStringMakeConstantString("\xef\xbf\xbd\x74\xef\xbf\xbd\x77\xef\xbf\xbd\x6f");

// CHECK-COFF: @.str = private unnamed_addr constant [4 x i8] c"one\00", align 1
// CHECK-ELF: @.str = private unnamed_addr constant [4 x i8] c"one\00", section ".rodata", align 1
// CHECK-MACHO: @.str = private unnamed_addr constant [4 x i8] c"one\00", section "__TEXT,__cstring,cstring_literals", align 1

// CHECK-COFF: @_unnamed_cfstring_ = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 1992, ptr @.str, i32 3 }, section "cfstring", align {{[48]}}
// CHECK-ELF32: @_unnamed_cfstring_ = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 1992, ptr @.str, i32 3 }, section "cfstring", align 4
// CHECK-ELF64: @_unnamed_cfstring_ = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 1992, ptr @.str, i64 3 }, section "cfstring", align 8
// CHECK-MACHO32: @_unnamed_cfstring_ = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 1992, ptr @.str, i32 3 }, section "__DATA,__cfstring", align 4
// CHECK-MACHO64: @_unnamed_cfstring_ = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 1992, ptr @.str, i64 3 }, section "__DATA,__cfstring", align 8

// CHECK-COFF: @.str.1 = private unnamed_addr constant [7 x i16] [i16 -3, i16 116, i16 -3, i16 119, i16 -3, i16 111, i16 0], align 2
// CHECK-ELF: @.str.1 = private unnamed_addr constant [7 x i16] [i16 -3, i16 116, i16 -3, i16 119, i16 -3, i16 111, i16 0], section ".rodata", align 2
// CHECK-MACHO: @.str.1 = private unnamed_addr constant [7 x i16] [i16 -3, i16 116, i16 -3, i16 119, i16 -3, i16 111, i16 0], section "__TEXT,__ustring", align 2

// CHECK-COFF: @_unnamed_cfstring_.2 = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 2000, ptr @.str.1, i32 6 }, section "cfstring", align {{[48]}}
// CHECK-ELF32: @_unnamed_cfstring_.2 = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 2000, ptr @.str.1, i32 6 }, section "cfstring", align 4
// CHECK-ELF64: @_unnamed_cfstring_.2 = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 2000, ptr @.str.1, i64 6 }, section "cfstring", align 8
// CHECK-MACHO32: @_unnamed_cfstring_.2 = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 2000, ptr @.str.1, i32 6 }, section "__DATA,__cfstring", align 4
// CHECK-MACHO64: @_unnamed_cfstring_.2 = private global %struct.__NSConstantString_tag { ptr @__CFConstantStringClassReference, i32 2000, ptr @.str.1, i64 6 }, section "__DATA,__cfstring", align 8

// CHECK-ASM-COFF: .section cfstring,"dw"
// CHECK-ASM-ELF: .section cfstring,"aw",{{[@%]}}progbits
// CHECK-ASM-MACHO: .section __DATA,__cfstring
