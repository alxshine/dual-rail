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
define dso_local void @printn_uart0(i8*, i32) #0 {
  %3 = alloca i8*, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i8* %0, i8** %3, align 4
  store i32 %1, i32* %4, align 4
  store i32 0, i32* %5, align 4
  br label %6

; <label>:6:                                      ; preds = %15, %2
  %7 = load i32, i32* %5, align 4
  %8 = load i32, i32* %4, align 4
  %9 = icmp slt i32 %7, %8
  br i1 %9, label %10, label %18

; <label>:10:                                     ; preds = %6
  %11 = load i8*, i8** %3, align 4
  %12 = getelementptr inbounds i8, i8* %11, i32 1
  store i8* %12, i8** %3, align 4
  %13 = load i8, i8* %11, align 1
  %14 = zext i8 %13 to i32
  store volatile i32 %14, i32* inttoptr (i32 270471168 to i32*), align 4
  br label %15

; <label>:15:                                     ; preds = %10
  %16 = load i32, i32* %5, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, i32* %5, align 4
  br label %6

; <label>:18:                                     ; preds = %6
  store volatile i32 10, i32* inttoptr (i32 270471168 to i32*), align 4
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @print_uart0(i8*) #0 {
  %2 = alloca i8*, align 4
  store i8* %0, i8** %2, align 4
  br label %3

; <label>:3:                                      ; preds = %8, %1
  %4 = load i8*, i8** %2, align 4
  %5 = load i8, i8* %4, align 1
  %6 = zext i8 %5 to i32
  %7 = icmp ne i32 %6, 0
  br i1 %7, label %8, label %14

; <label>:8:                                      ; preds = %3
  %9 = load i8*, i8** %2, align 4
  %10 = load i8, i8* %9, align 1
  %11 = zext i8 %10 to i32
  store volatile i32 %11, i32* inttoptr (i32 270471168 to i32*), align 4
  %12 = load i8*, i8** %2, align 4
  %13 = getelementptr inbounds i8, i8* %12, i32 1
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
  %3 = alloca i32, align 4
  %4 = alloca i8*, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i8* %1, i8** %4, align 4
  store i32 0, i32* %5, align 4
  %8 = load i8*, i8** %4, align 4
  %9 = load i32, i32* %5, align 4
  %10 = add nsw i32 %9, 1
  store i32 %10, i32* %5, align 4
  %11 = getelementptr inbounds i8, i8* %8, i32 %9
  store i8 48, i8* %11, align 1
  %12 = load i8*, i8** %4, align 4
  %13 = load i32, i32* %5, align 4
  %14 = add nsw i32 %13, 1
  store i32 %14, i32* %5, align 4
  %15 = getelementptr inbounds i8, i8* %12, i32 %13
  store i8 120, i8* %15, align 1
  store i32 28, i32* %6, align 4
  br label %16

; <label>:16:                                     ; preds = %33, %2
  %17 = load i32, i32* %6, align 4
  %18 = icmp sge i32 %17, 0
  br i1 %18, label %19, label %36

; <label>:19:                                     ; preds = %16
  %20 = load i32, i32* %6, align 4
  %21 = shl i32 15, %20
  %22 = load i32, i32* %3, align 4
  %23 = and i32 %21, %22
  %24 = load i32, i32* %6, align 4
  %25 = ashr i32 %23, %24
  store i32 %25, i32* %7, align 4
  %26 = load i32, i32* %7, align 4
  %27 = getelementptr inbounds [16 x i8], [16 x i8]* @hexChars, i32 0, i32 %26
  %28 = load i8, i8* %27, align 1
  %29 = load i8*, i8** %4, align 4
  %30 = load i32, i32* %5, align 4
  %31 = add nsw i32 %30, 1
  store i32 %31, i32* %5, align 4
  %32 = getelementptr inbounds i8, i8* %29, i32 %30
  store i8 %28, i8* %32, align 1
  br label %33

; <label>:33:                                     ; preds = %19
  %34 = load i32, i32* %6, align 4
  %35 = sub nsw i32 %34, 4
  store i32 %35, i32* %6, align 4
  br label %16

; <label>:36:                                     ; preds = %16
  %37 = load i8*, i8** %4, align 4
  %38 = load i32, i32* %5, align 4
  %39 = getelementptr inbounds i8, i8* %37, i32 %38
  store i8 0, i8* %39, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @c_entry() #0 {
  %1 = alloca [20 x i8], align 1 ;buffer
  %2 = alloca i32, align 4 ;i
  store i32 0, i32* %2, align 4
  br label %3

; <label>:3:                                      ; preds = %34, %0
  %4 = load i32, i32* %2, align 4
  %5 = icmp slt i32 %4, 10
  br i1 %5, label %6, label %37

; <label>:6:                                      ; preds = %3
  %7 = load i32, i32* %2, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %9, label %11

; <label>:9:                                      ; preds = %6
  %10 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @string_copy(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i32 0, i32 0), i8* %10, i32 8)
  br label %32

; <label>:11:                                     ; preds = %6
  %12 = load i32, i32* %2, align 4
  %13 = icmp eq i32 %12, 5
  br i1 %13, label %14, label %16

; <label>:14:                                     ; preds = %11
  %15 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @string_copy(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), i8* %15, i32 4)
  br label %31

; <label>:16:                                     ; preds = %11
  %17 = load i32, i32* %2, align 4
  %18 = icmp eq i32 %17, 3
  br i1 %18, label %25, label %19

; <label>:19:                                     ; preds = %16
  %20 = load i32, i32* %2, align 4
  %21 = icmp eq i32 %20, 6
  br i1 %21, label %25, label %22

; <label>:22:                                     ; preds = %19
  %23 = load i32, i32* %2, align 4
  %24 = icmp eq i32 %23, 9
  br i1 %24, label %25, label %27

; <label>:25:                                     ; preds = %22, %19, %16
  %26 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @string_copy(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8* %26, i32 4)
  br label %30

; <label>:27:                                     ; preds = %22
  %28 = load i32, i32* %2, align 4
  %29 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @write_int(i32 %28, i8* %29)
  br label %30

; <label>:30:                                     ; preds = %27, %25
  br label %31

; <label>:31:                                     ; preds = %30, %14
  br label %32

; <label>:32:                                     ; preds = %31, %9
  %33 = getelementptr inbounds [20 x i8], [20 x i8]* %1, i32 0, i32 0
  call void @print_uart0(i8* %33)
  br label %34

; <label>:34:                                     ; preds = %32
  %35 = load i32, i32* %2, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %2, align 4
  br label %3

; <label>:37:                                     ; preds = %3
  ret void
}

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="arm926ej-s" "target-features"="+armv5tej,+dsp,+strict-align,-crc,-dotprod,-hwdiv,-hwdiv-arm,-ras,-thumb-mode" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"min_enum_size", i32 4}
!2 = !{!"clang version 7.0.1 (tags/RELEASE_701/final)"}
