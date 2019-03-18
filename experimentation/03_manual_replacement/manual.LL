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
  %4 = alloca i8*, align 4
  %5 = alloca i8*, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i8* %0, i8** %4, align 4
  store i8* %1, i8** %5, align 4
  store i32 %2, i32* %6, align 4
  store i32 0, i32* %7, align 4
  br label %8

; <label>:8:                                      ; preds = %20, %3
  %9 = load i32, i32* %7, align 4
  %10 = load i32, i32* %6, align 4
  %11 = icmp slt i32 %9, %10
  br i1 %11, label %12, label %23

; <label>:12:                                     ; preds = %8
  %13 = load i8*, i8** %4, align 4
  %14 = load i32, i32* %7, align 4
  %15 = getelementptr inbounds i8, i8* %13, i32 %14
  %16 = load i8, i8* %15, align 1
  %17 = load i8*, i8** %5, align 4
  %18 = load i32, i32* %7, align 4
  %19 = getelementptr inbounds i8, i8* %17, i32 %18
  store i8 %16, i8* %19, align 1
  br label %20

; <label>:20:                                     ; preds = %12
  %21 = load i32, i32* %7, align 4
  %22 = add nsw i32 %21, 1
  store i32 %22, i32* %7, align 4
  br label %8

; <label>:23:                                     ; preds = %8
  %24 = load i8*, i8** %5, align 4
  %25 = load i32, i32* %6, align 4
  %26 = getelementptr inbounds i8, i8* %24, i32 %25
  store i8 0, i8* %26, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @write_int(i32, i8*) #0 {
  %3 = alloca i32, align 4 ;source
  %4 = alloca i8*, align 4 ;dest
  %5 = alloca i32, align 4 ;index
  %6 = alloca i32, align 4 ;i
  %7 = alloca i32, align 4 ;bits
  store i32 %0, i32* %3, align 4
  store i8* %1, i8** %4, align 4
  store i32 0, i32* %5, align 4 ;index = 0
  %8 = load i8*, i8** %4, align 4
  %9 = load i32, i32* %5, align 4 ;index
  %10 = add nsw i32 %9, 1 ;index+1
  store i32 %10, i32* %5, align 4 ;index = index+1
  %11 = getelementptr inbounds i8, i8* %8, i32 %9 ;load with non-incremented index
  store i8 48, i8* %11, align 1 ;store constant '0'
  %12 = load i8*, i8** %4, align 4
  %13 = load i32, i32* %5, align 4 ;index (is now 1)
  %14 = add nsw i32 %13, 1 ;index++
  store i32 %14, i32* %5, align 4 ;index = index+1 (now 2)
  %15 = getelementptr inbounds i8, i8* %12, i32 %13 ;load dest[index] (before increment)
  store i8 120, i8* %15, align 1 ;store constant 'x'
  store i32 28, i32* %6, align 4 ;i=28
  br label %16

; <label>:16:                                     ; preds = %33, %2
  %17 = load i32, i32* %6, align 4 ;i
  %18 = icmp sge i32 %17, 0 ;i>=0
  br i1 %18, label %19, label %36

; <label>:19:                                     ; preds = %16
  %20 = load i32, i32* %6, align 4 ;i
  %21 = shl i32 15, %20 ;0xf << i
  %22 = load i32, i32* %3, align 4 ;source
  %23 = and i32 %21, %22 ;tmp = (0xf << i) & source
  %24 = load i32, i32* %6, align 4 ;i
  %25 = ashr i32 %23, %24 ;tmp >> i
  store i32 %25, i32* %7, align 4 ;bits = tmp
  %26 = load i32, i32* %7, align 4 ;bits
  %27 = getelementptr inbounds [16 x i8], [16 x i8]* @hexChars, i32 0, i32 %26 ;&hexChars[bits]
  %28 = load i8, i8* %27, align 1 ;hexChars[bits]
  %29 = load i8*, i8** %4, align 4 ;dest
  %30 = load i32, i32* %5, align 4 ;index
  %31 = add nsw i32 %30, 1 ;index+1
  store i32 %31, i32* %5, align 4 ;index = index+1
  %32 = getelementptr inbounds i8, i8* %29, i32 %30 ;dest[index] (before increment)
  store i8 %28, i8* %32, align 1 ;dest[index] = hexChars[bits]
  br label %33

; <label>:33:                                     ; preds = %19
  %34 = load i32, i32* %6, align 4 ;i
  %35 = sub nsw i32 %34, 4 ;i-=4
  store i32 %35, i32* %6, align  4
  br label %16

; <label>:36:                                     ; preds = %16
  %37 = load i8*, i8** %4, align 4 ;dest
  %38 = load i32, i32* %5, align 4 ;index
  %39 = getelementptr inbounds i8, i8* %37, i32 %38
  store i8 0, i8* %39, align 1 ;dest[index] = '\0'
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
  call void @string_copy(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i32 0, i32 0), i8* %10, i32 8)
  br label %32

; <label>:11:                                     ; preds = %6
  %12 = load i32, i32* %2, align 4
  %13 = icmp eq i32 %12, 83950080 ;0x0500fa00
  br i1 %13, label %14, label %16

; <label>:14:                                     ; preds = %11
  %15 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @string_copy(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), i8* %15, i32 4)
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
  call void @string_copy(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8* %26, i32 4)
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
