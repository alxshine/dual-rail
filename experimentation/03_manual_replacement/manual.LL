; ModuleID = 'program.c'
source_filename = "program.c"
target datalayout = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "armv5e-none--eabi"

@UART0DR = dso_local constant i32* inttoptr (i32 270471168 to i32*), align 4
@hexChars = dso_local global [16 x i8] c"0123456789ABCDEF", align 1
@.str = private unnamed_addr constant [9 x i8] c"fizzbuzz\00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c"buzz\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"fizz\00", align 1

; Function Attrs: noinline nounwind optnone
define dso_local void @print_uart0(i8*) #0 {
  %2 = alloca i8*, align 4 ;s
  store i8* %0, i8** %2, align 4
  br label %3

; <label>:3:                                      ; preds = %8, %1
  %4 = load i8*, i8** %2, align 4 ;s
  %5 = load i8, i8* %4, align 1 ;*s
  %6 = zext i8 %5 to i32 ;(unsigned int)(*s)
  %7 = icmp ne i32 %6, 0 ;check in while
  br i1 %7, label %8, label %14

; <label>:8:                                      ; preds = %3
  %9 = load i8*, i8** %2, align 4 ;s
  %10 = load i8, i8* %9, align 1 ;*s
  %11 = zext i8 %10 to i32 ;(unsigned int) (*s)
  store volatile i32 %11, i32* inttoptr (i32 270471168 to i32*), align 4
  %12 = load i8*, i8** %2, align 4
  %13 = getelementptr inbounds i8, i8* %12, i32 1 ;increment pointer
  store i8* %13, i8** %2, align 4
  br label %3

; <label>:14:                                     ; preds = %3
  store volatile i32 10, i32* inttoptr (i32 270471168 to i32*), align 4
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @string_copy(i8*, i8*, i32) #0 {
  %4 = alloca i8*, align 4 ;source
  %5 = alloca i8*, align 4 ;dest
  %6 = alloca i32, align 4 ;n (comes in balanced)
  %7 = alloca i32, align 4 ;i
  store i8* %0, i8** %4, align 4
  store i8* %1, i8** %5, align 4
  store i32 %2, i32* %6, align 4
  store i32 65280, i32* %7, align 4 ;0x0000ff00
  br label %8

; <label>:8:
  %9 = load i32, i32* %7, align 4 ;i
  %10 = load i32, i32* %6, align 4 ;n
  %11 = icmp ult i32 %9, %10
  br i1 %11, label %12, label %27

; <label>:12:
  %13 = load i8*, i8** %4, align 4 ;source
  %14 = load i32, i32* %7, align 4 ;i
  %15 = lshr i32 %14, 24 ;unbalanced i
  %16 = getelementptr inbounds i8, i8* %13, i32 %15
  %17 = load i8, i8* %16, align 1 ;source[i]
  %18 = load i8*, i8** %5, align 4 ;dest
  %19 = load i32, i32* %7, align 4 ;i
  %20 = lshr i32 %19, 24 ;unbalanced i
  %21 = getelementptr inbounds i8, i8* %18, i32 %20
  store i8 %17, i8* %21, align 1
  br label %22

; <label>:22:
  %23 = load i32, i32* %7, align 4 ;i
  %24 = add i32 %23, 256 ;0x00000100
  %25 = add i32 %24, 16842240 ;0x0100fe00
  %26 = and i32 %25, 4278255360 ;0xff00ff00
  store i32 %26, i32* %7, align 4 ;store i
  br label %8

; <label>:27:
  %28 = load i8*, i8** %5, align 4 ;dest
  %29 = load i32, i32* %6, align 4 ;n
  %30 = lshr i32 %29, 24 ;unbalanced n
  %31 = getelementptr inbounds i8, i8* %28, i32 %30
  store i8 0, i8* %31, align 1 ;dest[n] = '\0'
  ret void
}

; ; Function Attrs: noinline nounwind optnone
; define dso_local void @string_copy(i8*, i8*, i32) #0 {
;   %4 = alloca i8*, align 4
;   %5 = alloca i8*, align 4
;   %6 = alloca i32, align 4
;   %7 = alloca i32, align 4
;   store i8* %0, i8** %4, align 4
;   store i8* %1, i8** %5, align 4
;   store i32 %2, i32* %6, align 4
;   store i32 0, i32* %7, align 4
;   br label %8

; ; <label>:8:                                      ; preds = %20, %3
;   %9 = load i32, i32* %7, align 4
;   %10 = load i32, i32* %6, align 4
;   %11 = icmp slt i32 %9, %10
;   br i1 %11, label %12, label %23

; ; <label>:12:                                     ; preds = %8
;   %13 = load i8*, i8** %4, align 4
;   %14 = load i32, i32* %7, align 4
;   %15 = getelementptr inbounds i8, i8* %13, i32 %14
;   %16 = load i8, i8* %15, align 1
;   %17 = load i8*, i8** %5, align 4
;   %18 = load i32, i32* %7, align 4
;   %19 = getelementptr inbounds i8, i8* %17, i32 %18
;   store i8 %16, i8* %19, align 1
;   br label %20

; ; <label>:20:                                     ; preds = %12
;   %21 = load i32, i32* %7, align 4
;   %22 = add nsw i32 %21, 1
;   store i32 %22, i32* %7, align 4
;   br label %8

; ; <label>:23:                                     ; preds = %8
;   %24 = load i8*, i8** %5, align 4
;   %25 = load i32, i32* %6, align 4
;   %26 = getelementptr inbounds i8, i8* %24, i32 %25
;   store i8 0, i8* %26, align 1
;   ret void
; }

define dso_local void @write_int(i32, i8*) #0 {
  %3 = alloca i32, align 4 ;source
  %4 = alloca i8*, align 4 ;dest
  %5 = alloca i32, align 4 ;index
  %6 = alloca i32, align 4 ;i
  %7 = alloca i32, align 4 ;bits
  store i32 %0, i32* %3, align 4
  store i8* %1, i8** %4, align 4
  store i32 65280, i32* %5, align 4 ;index = 0x0000ff00

  %8 = load i8*, i8** %4, align 4 ;dest
  %9 = load i32, i32* %5, align 4 ;index
  %10 = lshr i32 %9, 24 ;unbalanced index
  %11 = add nsw i32 %9, 256
  %12 = add nsw i32 %11, 16842240 ;0x0100fe00
  %13 = and i32 %12, 4278255360 ;0xff00ff00
  store i32 %13, i32* %5, align 4 ;index = index+1
  %14 = getelementptr inbounds i8, i8* %8, i32 %10 ;load from unbalanced index
  store i8 48, i8* %14, align 1 ;store constant '0'

  %15 = load i8*, i8** %4, align 4 ;dest
  %16 = load i32, i32* %5, align 4 ;index
  %17 = lshr i32 %16, 24 ;unbalanced index
  %18 = add nsw i32 %16, 256
  %19 = add nsw i32 %18, 16842240 ;0x0100fe00
  %20 = and i32 %19, 4278255360 ;0xff00ff00
  store i32 %20, i32* %5, align 4 ;index = index+1
  %21 = getelementptr inbounds i8, i8* %15, i32 %17 ;load from unbalanced index
  store i8 120, i8* %21, align 1 ;store constant 'x'

  store i32 469820160, i32* %6, align 4 ;i=0x1c00e300 (balanced 28)
  br label %22

; <label>: 22:			;preds = %2
  %23 = load i32, i32* %6, align 4 ;i
  %24 = icmp sge i32 %23, 65280 ;i>= 0x0000ff00
  br i1 %24, label %25, label %58

; <label>: 25:
  %26 = load i32, i32* %6, align 4 ;i
  %27 = lshr i32 %26, 24 ;unbalanced i for shift
  %28 = shl i32 15, %27 ;0xf << i
  %29 = load i32, i32* %3, align 4 ;source
  %30 = and i32 %28, %29 ;tmp = (0xf << i) & source
  %31 = load i32, i32* %6, align 4 ;i
  %32 = lshr i32 %31, 24 ;unbalanced i for shift
  %33 = lshr i32 %30, %32 ;tmp >> i
  store i32 %33, i32* %7, align 4 ;bits = tmp
  %34 = load i32, i32* %7, align 4 ;bits
  %35 = getelementptr inbounds [16 x i8], [16 x i8]* @hexChars, i32 0, i32 %34 ;&hexChars[bits]
  %36 = load i8, i8* %35, align 1 ;hexChars[bits]
  %37 = load i8*, i8** %4, align 4 ;dest
  %38 = load i32, i32* %5, align 4 ;index
  %39 = lshr i32 %38, 24 ;unbalanced index
  %40 = add nsw i32 %38, 256
  %41 = add nsw i32 %40, 16842240 ;0x0100fe00
  %42 = and i32 %41, 4278255360 ;0xff00ff00
  store i32 %42, i32* %5, align 4 ;index = index+1
  %43 = getelementptr inbounds i8, i8* %37, i32 %39 ;&dest[index]
  store i8 %36, i8* %43, align 1 ;dest[index] = hexChars[bits]
  br label %44

; <label>: 44:
  %45 = load i32, i32* %6, align 4 ;i
  %46 = add i32 %45, 4227859712 ; ~0x0400fb00+0x00010001 (corrected two's complement)
  %47 = add i32 %45, 4211082240 ;0xfb000400 (negation of before)
  %48 = and i32 %46, -16711936 ;0xff00ff00 filter
  %49 = and i32 %47, -16711936 ;0xff00ff00 filter
  %50 = lshr i32 %49, 8
  %51 = or i32 %48, %50 ;subtraction
  %52 = and i32 %51, 4278190335; 0xff0000ff (filtering after subtraction)
  ;changing balancing:
  %53 = shl i32 %52, 8
  %54 = lshr i32 %52, 24
  %55 = or i32 %53, %54 ;rotated left by 8 (right by 28)
  %56 = or i32 %52, %55
  %57 = and i32 %56, 4278255360 ;0xff00ff00 (filtering for balancing scheme 1)
  
  store i32 %57, i32* %6, align 4 ;store i
  br label %22

; <label>: 58:
  %59 = load i8*, i8** %4, align 4 ;dest
  %60 = load i32, i32* %5, align 4 ;index
  %61 = lshr i32 %60, 24 ;unbalanced index
  %62 = getelementptr inbounds i8, i8* %59, i32 %61
  store i8 0, i8* %62, align 1 ;dest[index] = '\0'
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @c_entry() #0 {
  %1 = alloca [20 x i8], align 1 ;buffer
  %2 = alloca i32, align 4 ;i
  store i32 65280, i32* %2, align 4 ;0x0000ff00
  br label %3

; <label>:3:                                      ; preds = %34, %0
  %4 = load i32, i32* %2, align 4
  %5 = icmp slt i32 %4, 167772405 ;0x0A00F500
  br i1 %5, label %6, label %40

; <label>:6:                                      ; preds = %3
  %7 = load i32, i32* %2, align 4
  %8 = icmp eq i32 %7, 65280 ;0x0000ff00
  br i1 %8, label %9, label %11

; <label>:9:                                      ; preds = %6
  %10 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @string_copy(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i32 0, i32 0), i8* %10, i32 134280960) ;0x0800f700
  ; call void @string_copy(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i32 0, i32 0), i8* %10, i32 8)
  br label %32

; <label>:11:                                     ; preds = %6
  %12 = load i32, i32* %2, align 4
  %13 = icmp eq i32 %12, 83950080 ;0x0500fa00
  br i1 %13, label %14, label %16

; <label>:14:                                     ; preds = %11
  %15 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @string_copy(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), i8* %15, i32 67173120) ;0x0400fb00
  ; call void @string_copy(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), i8* %15, i32 8)
  br label %31

; <label>:16:                                     ; preds = %11
  %17 = load i32, i32* %2, align 4
  %18 = icmp eq i32 %17, 50396160 ;0x0300fc00
  br i1 %18, label %25, label %19

; <label>:19:                                     ; preds = %16
  %20 = load i32, i32* %2, align 4
  %21 = icmp eq i32 %20, 100727040 ;0x0600f900
  br i1 %21, label %25, label %22

; <label>:22:                                     ; preds = %19
  %23 = load i32, i32* %2, align 4
  %24 = icmp eq i32 %23, 151057920 ;0x0900f600
  br i1 %24, label %25, label %27

; <label>:25:                                     ; preds = %22, %19, %16
  %26 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @string_copy(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8* %26, i32 67173120) ;0x0400fb00
  ; call void @string_copy(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8* %26, i32 4)
  br label %31

; <label>:27:                                     ; preds = %22
  %28 = load i32, i32* %2, align 4
  %29 = lshr i32 %28, 24
  %30 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @write_int(i32 %29, i8* %30)
  br label %31

; <label>:31:                                     ; preds = %27, %25
  br label %32

; <label>:32:                                     ; preds = %30, %14
  br label %33

; <label>:33:                                     ; preds = %31, %9
  %34 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @print_uart0(i8* %34)
  br label %35

; <label>:35:                                     ; preds = %32
  %36 = load i32, i32* %2, align 4
  %37 = add nsw i32 %36, 256 ;0x00000100
  %38 = add nsw i32 %37, 16842240 ;0x0100fe00
  %39 = and i32 %38, 4278255360 ;0xff00ff00
  store i32 %39, i32* %2, align 4
  br label %3

; <label>:40:                                     ; preds = %3
  ret void
}

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="arm926ej-s" "target-features"="+armv5tej,+dsp,+strict-align,-crc,-dotprod,-hwdiv,-hwdiv-arm,-ras,-thumb-mode" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"min_enum_size", i32 4}
!2 = !{!"clang version 7.0.1 (tags/RELEASE_701/final)"}
