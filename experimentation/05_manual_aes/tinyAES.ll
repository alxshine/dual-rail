; ModuleID = 'tinyAES.c'
source_filename = "tinyAES.c"
target datalayout = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"
target triple = "armv5e-none--eabi"

@state = internal global [4 x [4 x i8]]* null, align 4
@Key = internal global i8* null, align 4
@RoundKey = internal global [176 x i8] zeroinitializer, align 1
@Rcon = internal constant [255 x i8] c"\8D\01\02\04\08\10 @\80\1B6l\D8\ABM\9A/^\BCc\C6\975j\D4\B3}\FA\EF\C5\919r\E4\D3\BDa\C2\9F%J\943f\CC\83\1D:t\E8\CB\8D\01\02\04\08\10 @\80\1B6l\D8\ABM\9A/^\BCc\C6\975j\D4\B3}\FA\EF\C5\919r\E4\D3\BDa\C2\9F%J\943f\CC\83\1D:t\E8\CB\8D\01\02\04\08\10 @\80\1B6l\D8\ABM\9A/^\BCc\C6\975j\D4\B3}\FA\EF\C5\919r\E4\D3\BDa\C2\9F%J\943f\CC\83\1D:t\E8\CB\8D\01\02\04\08\10 @\80\1B6l\D8\ABM\9A/^\BCc\C6\975j\D4\B3}\FA\EF\C5\919r\E4\D3\BDa\C2\9F%J\943f\CC\83\1D:t\E8\CB\8D\01\02\04\08\10 @\80\1B6l\D8\ABM\9A/^\BCc\C6\975j\D4\B3}\FA\EF\C5\919r\E4\D3\BDa\C2\9F%J\943f\CC\83\1D:t\E8\CB", align 1
@sbox = internal constant [256 x i8] c"c|w{\F2ko\C50\01g+\FE\D7\ABv\CA\82\C9}\FAYG\F0\AD\D4\A2\AF\9C\A4r\C0\B7\FD\93&6?\F7\CC4\A5\E5\F1q\D81\15\04\C7#\C3\18\96\05\9A\07\12\80\E2\EB'\B2u\09\83,\1A\1BnZ\A0R;\D6\B3)\E3/\84S\D1\00\ED \FC\B1[j\CB\BE9JLX\CF\D0\EF\AA\FBCM3\85E\F9\02\7FP<\9F\A8Q\A3@\8F\92\9D8\F5\BC\B6\DA!\10\FF\F3\D2\CD\0C\13\EC_\97D\17\C4\A7~=d]\19s`\81O\DC\22*\90\88F\EE\B8\14\DE^\0B\DB\E02:\0AI\06$\5C\C2\D3\ACb\91\95\E4y\E7\C87m\8D\D5N\A9lV\F4\EAez\AE\08\BAx%.\1C\A6\B4\C6\E8\DDt\1FK\BD\8B\8Ap>\B5fH\03\F6\0Ea5W\B9\86\C1\1D\9E\E1\F8\98\11i\D9\8E\94\9B\1E\87\E9\CEU(\DF\8C\A1\89\0D\BF\E6BhA\99-\0F\B0T\BB\16", align 1
@rsbox = internal constant [256 x i8] c"R\09j\D506\A58\BF@\A3\9E\81\F3\D7\FB|\E39\82\9B/\FF\874\8ECD\C4\DE\E9\CBT{\942\A6\C2#=\EEL\95\0BB\FA\C3N\08.\A1f(\D9$\B2v[\A2Im\8B\D1%r\F8\F6d\86h\98\16\D4\A4\5C\CC]e\B6\92lpHP\FD\ED\B9\DA^\15FW\A7\8D\9D\84\90\D8\AB\00\8C\BC\D3\0A\F7\E4X\05\B8\B3E\06\D0,\1E\8F\CA?\0F\02\C1\AF\BD\03\01\13\8Ak:\91\11AOg\DC\EA\97\F2\CF\CE\F0\B4\E6s\96\ACt\22\E7\AD5\85\E2\F97\E8\1Cu\DFnG\F1\1Aq\1D)\C5\89o\B7b\0E\AA\18\BE\1B\FCV>K\C6\D2y \9A\DB\C0\FEx\CDZ\F4\1F\DD\A83\88\07\C71\B1\12\10Y'\80\EC_`Q\7F\A9\19\B5J\0D-\E5z\9F\93\C9\9C\EF\A0\E0;M\AE*\F5\B0\C8\EB\BB<\83S\99a\17+\04~\BAw\D6&\E1i\14cU!\0C}", align 1

; Function Attrs: noinline nounwind optnone
define dso_local void @AES128_ECB_encrypt(i8*, i8*, i8*) #0 {
  %4 = alloca i8*, align 4
  %5 = alloca i8*, align 4
  %6 = alloca i8*, align 4
  store i8* %0, i8** %4, align 4
  store i8* %1, i8** %5, align 4
  store i8* %2, i8** %6, align 4
  %7 = load i8*, i8** %6, align 4
  %8 = load i8*, i8** %4, align 4
  call void @BlockCopy(i8* %7, i8* %8)
  %9 = load i8*, i8** %6, align 4
  %10 = bitcast i8* %9 to [4 x [4 x i8]]*
  store [4 x [4 x i8]]* %10, [4 x [4 x i8]]** @state, align 4
  %11 = load i8*, i8** %5, align 4
  store i8* %11, i8** @Key, align 4
  call void @KeyExpansion()
  call void @Cipher()
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal void @BlockCopy(i8*, i8*) #0 {
  %3 = alloca i8*, align 4
  %4 = alloca i8*, align 4
  %5 = alloca i8, align 1
  store i8* %0, i8** %3, align 4
  store i8* %1, i8** %4, align 4
  store i8 0, i8* %5, align 1
  br label %6

; <label>:6:                                      ; preds = %20, %2
  %7 = load i8, i8* %5, align 1
  %8 = zext i8 %7 to i32
  %9 = icmp slt i32 %8, 16
  br i1 %9, label %10, label %23

; <label>:10:                                     ; preds = %6
  %11 = load i8*, i8** %4, align 4
  %12 = load i8, i8* %5, align 1
  %13 = zext i8 %12 to i32
  %14 = getelementptr inbounds i8, i8* %11, i32 %13
  %15 = load i8, i8* %14, align 1
  %16 = load i8*, i8** %3, align 4
  %17 = load i8, i8* %5, align 1
  %18 = zext i8 %17 to i32
  %19 = getelementptr inbounds i8, i8* %16, i32 %18
  store i8 %15, i8* %19, align 1
  br label %20

; <label>:20:                                     ; preds = %10
  %21 = load i8, i8* %5, align 1
  %22 = add i8 %21, 1
  store i8 %22, i8* %5, align 1
  br label %6

; <label>:23:                                     ; preds = %6
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal void @KeyExpansion() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca [4 x i8], align 1
  store i32 0, i32* %1, align 4
  br label %5

; <label>:5:                                      ; preds = %49, %0
  %6 = load i32, i32* %1, align 4
  %7 = icmp ult i32 %6, 4
  br i1 %7, label %8, label %52

; <label>:8:                                      ; preds = %5
  %9 = load i8*, i8** @Key, align 4
  %10 = load i32, i32* %1, align 4
  %11 = mul i32 %10, 4
  %12 = add i32 %11, 0
  %13 = getelementptr inbounds i8, i8* %9, i32 %12
  %14 = load i8, i8* %13, align 1
  %15 = load i32, i32* %1, align 4
  %16 = mul i32 %15, 4
  %17 = add i32 %16, 0
  %18 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %17
  store i8 %14, i8* %18, align 1
  %19 = load i8*, i8** @Key, align 4
  %20 = load i32, i32* %1, align 4
  %21 = mul i32 %20, 4
  %22 = add i32 %21, 1
  %23 = getelementptr inbounds i8, i8* %19, i32 %22
  %24 = load i8, i8* %23, align 1
  %25 = load i32, i32* %1, align 4
  %26 = mul i32 %25, 4
  %27 = add i32 %26, 1
  %28 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %27
  store i8 %24, i8* %28, align 1
  %29 = load i8*, i8** @Key, align 4
  %30 = load i32, i32* %1, align 4
  %31 = mul i32 %30, 4
  %32 = add i32 %31, 2
  %33 = getelementptr inbounds i8, i8* %29, i32 %32
  %34 = load i8, i8* %33, align 1
  %35 = load i32, i32* %1, align 4
  %36 = mul i32 %35, 4
  %37 = add i32 %36, 2
  %38 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %37
  store i8 %34, i8* %38, align 1
  %39 = load i8*, i8** @Key, align 4
  %40 = load i32, i32* %1, align 4
  %41 = mul i32 %40, 4
  %42 = add i32 %41, 3
  %43 = getelementptr inbounds i8, i8* %39, i32 %42
  %44 = load i8, i8* %43, align 1
  %45 = load i32, i32* %1, align 4
  %46 = mul i32 %45, 4
  %47 = add i32 %46, 3
  %48 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %47
  store i8 %44, i8* %48, align 1
  br label %49

; <label>:49:                                     ; preds = %8
  %50 = load i32, i32* %1, align 4
  %51 = add i32 %50, 1
  store i32 %51, i32* %1, align 4
  br label %5

; <label>:52:                                     ; preds = %5
  br label %53

; <label>:53:                                     ; preds = %186, %52
  %54 = load i32, i32* %1, align 4
  %55 = icmp ult i32 %54, 44
  br i1 %55, label %56, label %189

; <label>:56:                                     ; preds = %53
  store i32 0, i32* %2, align 4
  br label %57

; <label>:57:                                     ; preds = %70, %56
  %58 = load i32, i32* %2, align 4
  %59 = icmp ult i32 %58, 4
  br i1 %59, label %60, label %73

; <label>:60:                                     ; preds = %57
  %61 = load i32, i32* %1, align 4
  %62 = sub i32 %61, 1
  %63 = mul i32 %62, 4
  %64 = load i32, i32* %2, align 4
  %65 = add i32 %63, %64
  %66 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %65
  %67 = load i8, i8* %66, align 1
  %68 = load i32, i32* %2, align 4
  %69 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 %68
  store i8 %67, i8* %69, align 1
  br label %70

; <label>:70:                                     ; preds = %60
  %71 = load i32, i32* %2, align 4
  %72 = add i32 %71, 1
  store i32 %72, i32* %2, align 4
  br label %57

; <label>:73:                                     ; preds = %57
  %74 = load i32, i32* %1, align 4
  %75 = urem i32 %74, 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %77, label %120

; <label>:77:                                     ; preds = %73
  %78 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 0
  %79 = load i8, i8* %78, align 1
  %80 = zext i8 %79 to i32
  store i32 %80, i32* %3, align 4
  %81 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 1
  %82 = load i8, i8* %81, align 1
  %83 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 0
  store i8 %82, i8* %83, align 1
  %84 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 2
  %85 = load i8, i8* %84, align 1
  %86 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 1
  store i8 %85, i8* %86, align 1
  %87 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 3
  %88 = load i8, i8* %87, align 1
  %89 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 2
  store i8 %88, i8* %89, align 1
  %90 = load i32, i32* %3, align 4
  %91 = trunc i32 %90 to i8
  %92 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 3
  store i8 %91, i8* %92, align 1
  %93 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 0
  %94 = load i8, i8* %93, align 1
  %95 = call zeroext i8 @getSBoxValue(i8 zeroext %94)
  %96 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 0
  store i8 %95, i8* %96, align 1
  %97 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 1
  %98 = load i8, i8* %97, align 1
  %99 = call zeroext i8 @getSBoxValue(i8 zeroext %98)
  %100 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 1
  store i8 %99, i8* %100, align 1
  %101 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 2
  %102 = load i8, i8* %101, align 1
  %103 = call zeroext i8 @getSBoxValue(i8 zeroext %102)
  %104 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 2
  store i8 %103, i8* %104, align 1
  %105 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 3
  %106 = load i8, i8* %105, align 1
  %107 = call zeroext i8 @getSBoxValue(i8 zeroext %106)
  %108 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 3
  store i8 %107, i8* %108, align 1
  %109 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 0
  %110 = load i8, i8* %109, align 1
  %111 = zext i8 %110 to i32
  %112 = load i32, i32* %1, align 4
  %113 = udiv i32 %112, 4
  %114 = getelementptr inbounds [255 x i8], [255 x i8]* @Rcon, i32 0, i32 %113
  %115 = load i8, i8* %114, align 1
  %116 = zext i8 %115 to i32
  %117 = xor i32 %111, %116
  %118 = trunc i32 %117 to i8
  %119 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 0
  store i8 %118, i8* %119, align 1
  br label %121

; <label>:120:                                    ; preds = %73
  br label %121

; <label>:121:                                    ; preds = %120, %77
  %122 = load i32, i32* %1, align 4
  %123 = sub i32 %122, 4
  %124 = mul i32 %123, 4
  %125 = add i32 %124, 0
  %126 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %125
  %127 = load i8, i8* %126, align 1
  %128 = zext i8 %127 to i32
  %129 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 0
  %130 = load i8, i8* %129, align 1
  %131 = zext i8 %130 to i32
  %132 = xor i32 %128, %131
  %133 = trunc i32 %132 to i8
  %134 = load i32, i32* %1, align 4
  %135 = mul i32 %134, 4
  %136 = add i32 %135, 0
  %137 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %136
  store i8 %133, i8* %137, align 1
  %138 = load i32, i32* %1, align 4
  %139 = sub i32 %138, 4
  %140 = mul i32 %139, 4
  %141 = add i32 %140, 1
  %142 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %141
  %143 = load i8, i8* %142, align 1
  %144 = zext i8 %143 to i32
  %145 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 1
  %146 = load i8, i8* %145, align 1
  %147 = zext i8 %146 to i32
  %148 = xor i32 %144, %147
  %149 = trunc i32 %148 to i8
  %150 = load i32, i32* %1, align 4
  %151 = mul i32 %150, 4
  %152 = add i32 %151, 1
  %153 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %152
  store i8 %149, i8* %153, align 1
  %154 = load i32, i32* %1, align 4
  %155 = sub i32 %154, 4
  %156 = mul i32 %155, 4
  %157 = add i32 %156, 2
  %158 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %157
  %159 = load i8, i8* %158, align 1
  %160 = zext i8 %159 to i32
  %161 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 2
  %162 = load i8, i8* %161, align 1
  %163 = zext i8 %162 to i32
  %164 = xor i32 %160, %163
  %165 = trunc i32 %164 to i8
  %166 = load i32, i32* %1, align 4
  %167 = mul i32 %166, 4
  %168 = add i32 %167, 2
  %169 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %168
  store i8 %165, i8* %169, align 1
  %170 = load i32, i32* %1, align 4
  %171 = sub i32 %170, 4
  %172 = mul i32 %171, 4
  %173 = add i32 %172, 3
  %174 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %173
  %175 = load i8, i8* %174, align 1
  %176 = zext i8 %175 to i32
  %177 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 3
  %178 = load i8, i8* %177, align 1
  %179 = zext i8 %178 to i32
  %180 = xor i32 %176, %179
  %181 = trunc i32 %180 to i8
  %182 = load i32, i32* %1, align 4
  %183 = mul i32 %182, 4
  %184 = add i32 %183, 3
  %185 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %184
  store i8 %181, i8* %185, align 1
  br label %186

; <label>:186:                                    ; preds = %121
  %187 = load i32, i32* %1, align 4
  %188 = add i32 %187, 1
  store i32 %188, i32* %1, align 4
  br label %53

; <label>:189:                                    ; preds = %53
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal void @Cipher() #0 {
  %1 = alloca i8, align 1
  store i8 0, i8* %1, align 1
  call void @AddRoundKey(i8 zeroext 0)
  store i8 1, i8* %1, align 1
  br label %2

; <label>:2:                                      ; preds = %8, %0
  %3 = load i8, i8* %1, align 1
  %4 = zext i8 %3 to i32
  %5 = icmp slt i32 %4, 10
  br i1 %5, label %6, label %11

; <label>:6:                                      ; preds = %2
  call void @SubBytes()
  call void @ShiftRows()
  call void @MixColumns()
  %7 = load i8, i8* %1, align 1
  call void @AddRoundKey(i8 zeroext %7)
  br label %8

; <label>:8:                                      ; preds = %6
  %9 = load i8, i8* %1, align 1
  %10 = add i8 %9, 1
  store i8 %10, i8* %1, align 1
  br label %2

; <label>:11:                                     ; preds = %2
  call void @SubBytes()
  call void @ShiftRows()
  call void @AddRoundKey(i8 zeroext 10)
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @AES128_ECB_decrypt(i8*, i8*, i8*) #0 {
  %4 = alloca i8*, align 4
  %5 = alloca i8*, align 4
  %6 = alloca i8*, align 4
  store i8* %0, i8** %4, align 4
  store i8* %1, i8** %5, align 4
  store i8* %2, i8** %6, align 4
  %7 = load i8*, i8** %6, align 4
  %8 = load i8*, i8** %4, align 4
  call void @BlockCopy(i8* %7, i8* %8)
  %9 = load i8*, i8** %6, align 4
  %10 = bitcast i8* %9 to [4 x [4 x i8]]*
  store [4 x [4 x i8]]* %10, [4 x [4 x i8]]** @state, align 4
  %11 = load i8*, i8** %5, align 4
  store i8* %11, i8** @Key, align 4
  call void @KeyExpansion()
  call void @InvCipher()
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal void @InvCipher() #0 {
  %1 = alloca i8, align 1
  store i8 0, i8* %1, align 1
  call void @AddRoundKey(i8 zeroext 10)
  store i8 9, i8* %1, align 1
  br label %2

; <label>:2:                                      ; preds = %8, %0
  %3 = load i8, i8* %1, align 1
  %4 = zext i8 %3 to i32
  %5 = icmp sgt i32 %4, 0
  br i1 %5, label %6, label %11

; <label>:6:                                      ; preds = %2
  call void @InvShiftRows()
  call void @InvSubBytes()
  %7 = load i8, i8* %1, align 1
  call void @AddRoundKey(i8 zeroext %7)
  call void @InvMixColumns()
  br label %8

; <label>:8:                                      ; preds = %6
  %9 = load i8, i8* %1, align 1
  %10 = add i8 %9, -1
  store i8 %10, i8* %1, align 1
  br label %2

; <label>:11:                                     ; preds = %2
  call void @InvShiftRows()
  call void @InvSubBytes()
  call void @AddRoundKey(i8 zeroext 0)
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal zeroext i8 @getSBoxValue(i8 zeroext) #0 {
  %2 = alloca i8, align 1
  store i8 %0, i8* %2, align 1
  %3 = load i8, i8* %2, align 1
  %4 = zext i8 %3 to i32
  %5 = getelementptr inbounds [256 x i8], [256 x i8]* @sbox, i32 0, i32 %4
  %6 = load i8, i8* %5, align 1
  ret i8 %6
}

; Function Attrs: noinline nounwind optnone
define internal void @AddRoundKey(i8 zeroext) #0 {
  %2 = alloca i8, align 1
  %3 = alloca i8, align 1
  %4 = alloca i8, align 1
  store i8 %0, i8* %2, align 1
  store i8 0, i8* %3, align 1
  br label %5

; <label>:5:                                      ; preds = %44, %1
  %6 = load i8, i8* %3, align 1
  %7 = zext i8 %6 to i32
  %8 = icmp slt i32 %7, 4
  br i1 %8, label %9, label %47

; <label>:9:                                      ; preds = %5
  store i8 0, i8* %4, align 1
  br label %10

; <label>:10:                                     ; preds = %40, %9
  %11 = load i8, i8* %4, align 1
  %12 = zext i8 %11 to i32
  %13 = icmp slt i32 %12, 4
  br i1 %13, label %14, label %43

; <label>:14:                                     ; preds = %10
  %15 = load i8, i8* %2, align 1
  %16 = zext i8 %15 to i32
  %17 = mul nsw i32 %16, 4
  %18 = mul nsw i32 %17, 4
  %19 = load i8, i8* %3, align 1
  %20 = zext i8 %19 to i32
  %21 = mul nsw i32 %20, 4
  %22 = add nsw i32 %18, %21
  %23 = load i8, i8* %4, align 1
  %24 = zext i8 %23 to i32
  %25 = add nsw i32 %22, %24
  %26 = getelementptr inbounds [176 x i8], [176 x i8]* @RoundKey, i32 0, i32 %25
  %27 = load i8, i8* %26, align 1
  %28 = zext i8 %27 to i32
  %29 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %30 = load i8, i8* %3, align 1
  %31 = zext i8 %30 to i32
  %32 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %29, i32 0, i32 %31
  %33 = load i8, i8* %4, align 1
  %34 = zext i8 %33 to i32
  %35 = getelementptr inbounds [4 x i8], [4 x i8]* %32, i32 0, i32 %34
  %36 = load i8, i8* %35, align 1
  %37 = zext i8 %36 to i32
  %38 = xor i32 %37, %28
  %39 = trunc i32 %38 to i8
  store i8 %39, i8* %35, align 1
  br label %40

; <label>:40:                                     ; preds = %14
  %41 = load i8, i8* %4, align 1
  %42 = add i8 %41, 1
  store i8 %42, i8* %4, align 1
  br label %10

; <label>:43:                                     ; preds = %10
  br label %44

; <label>:44:                                     ; preds = %43
  %45 = load i8, i8* %3, align 1
  %46 = add i8 %45, 1
  store i8 %46, i8* %3, align 1
  br label %5

; <label>:47:                                     ; preds = %5
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal void @SubBytes() #0 {
  %1 = alloca i8, align 1
  %2 = alloca i8, align 1
  store i8 0, i8* %1, align 1
  br label %3

; <label>:3:                                      ; preds = %33, %0
  %4 = load i8, i8* %1, align 1
  %5 = zext i8 %4 to i32
  %6 = icmp slt i32 %5, 4
  br i1 %6, label %7, label %36

; <label>:7:                                      ; preds = %3
  store i8 0, i8* %2, align 1
  br label %8

; <label>:8:                                      ; preds = %29, %7
  %9 = load i8, i8* %2, align 1
  %10 = zext i8 %9 to i32
  %11 = icmp slt i32 %10, 4
  br i1 %11, label %12, label %32

; <label>:12:                                     ; preds = %8
  %13 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %14 = load i8, i8* %2, align 1
  %15 = zext i8 %14 to i32
  %16 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %13, i32 0, i32 %15
  %17 = load i8, i8* %1, align 1
  %18 = zext i8 %17 to i32
  %19 = getelementptr inbounds [4 x i8], [4 x i8]* %16, i32 0, i32 %18
  %20 = load i8, i8* %19, align 1
  %21 = call zeroext i8 @getSBoxValue(i8 zeroext %20)
  %22 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %23 = load i8, i8* %2, align 1
  %24 = zext i8 %23 to i32
  %25 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %22, i32 0, i32 %24
  %26 = load i8, i8* %1, align 1
  %27 = zext i8 %26 to i32
  %28 = getelementptr inbounds [4 x i8], [4 x i8]* %25, i32 0, i32 %27
  store i8 %21, i8* %28, align 1
  br label %29

; <label>:29:                                     ; preds = %12
  %30 = load i8, i8* %2, align 1
  %31 = add i8 %30, 1
  store i8 %31, i8* %2, align 1
  br label %8

; <label>:32:                                     ; preds = %8
  br label %33

; <label>:33:                                     ; preds = %32
  %34 = load i8, i8* %1, align 1
  %35 = add i8 %34, 1
  store i8 %35, i8* %1, align 1
  br label %3

; <label>:36:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal void @ShiftRows() #0 {
  %1 = alloca i8, align 1
  %2 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %3 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %2, i32 0, i32 0
  %4 = getelementptr inbounds [4 x i8], [4 x i8]* %3, i32 0, i32 1
  %5 = load i8, i8* %4, align 1
  store i8 %5, i8* %1, align 1
  %6 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %7 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %6, i32 0, i32 1
  %8 = getelementptr inbounds [4 x i8], [4 x i8]* %7, i32 0, i32 1
  %9 = load i8, i8* %8, align 1
  %10 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %11 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %10, i32 0, i32 0
  %12 = getelementptr inbounds [4 x i8], [4 x i8]* %11, i32 0, i32 1
  store i8 %9, i8* %12, align 1
  %13 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %14 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %13, i32 0, i32 2
  %15 = getelementptr inbounds [4 x i8], [4 x i8]* %14, i32 0, i32 1
  %16 = load i8, i8* %15, align 1
  %17 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %18 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %17, i32 0, i32 1
  %19 = getelementptr inbounds [4 x i8], [4 x i8]* %18, i32 0, i32 1
  store i8 %16, i8* %19, align 1
  %20 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %21 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %20, i32 0, i32 3
  %22 = getelementptr inbounds [4 x i8], [4 x i8]* %21, i32 0, i32 1
  %23 = load i8, i8* %22, align 1
  %24 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %25 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %24, i32 0, i32 2
  %26 = getelementptr inbounds [4 x i8], [4 x i8]* %25, i32 0, i32 1
  store i8 %23, i8* %26, align 1
  %27 = load i8, i8* %1, align 1
  %28 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %29 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %28, i32 0, i32 3
  %30 = getelementptr inbounds [4 x i8], [4 x i8]* %29, i32 0, i32 1
  store i8 %27, i8* %30, align 1
  %31 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %32 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %31, i32 0, i32 0
  %33 = getelementptr inbounds [4 x i8], [4 x i8]* %32, i32 0, i32 2
  %34 = load i8, i8* %33, align 1
  store i8 %34, i8* %1, align 1
  %35 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %36 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %35, i32 0, i32 2
  %37 = getelementptr inbounds [4 x i8], [4 x i8]* %36, i32 0, i32 2
  %38 = load i8, i8* %37, align 1
  %39 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %40 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %39, i32 0, i32 0
  %41 = getelementptr inbounds [4 x i8], [4 x i8]* %40, i32 0, i32 2
  store i8 %38, i8* %41, align 1
  %42 = load i8, i8* %1, align 1
  %43 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %44 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %43, i32 0, i32 2
  %45 = getelementptr inbounds [4 x i8], [4 x i8]* %44, i32 0, i32 2
  store i8 %42, i8* %45, align 1
  %46 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %47 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %46, i32 0, i32 1
  %48 = getelementptr inbounds [4 x i8], [4 x i8]* %47, i32 0, i32 2
  %49 = load i8, i8* %48, align 1
  store i8 %49, i8* %1, align 1
  %50 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %51 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %50, i32 0, i32 3
  %52 = getelementptr inbounds [4 x i8], [4 x i8]* %51, i32 0, i32 2
  %53 = load i8, i8* %52, align 1
  %54 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %55 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %54, i32 0, i32 1
  %56 = getelementptr inbounds [4 x i8], [4 x i8]* %55, i32 0, i32 2
  store i8 %53, i8* %56, align 1
  %57 = load i8, i8* %1, align 1
  %58 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %59 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %58, i32 0, i32 3
  %60 = getelementptr inbounds [4 x i8], [4 x i8]* %59, i32 0, i32 2
  store i8 %57, i8* %60, align 1
  %61 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %62 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %61, i32 0, i32 0
  %63 = getelementptr inbounds [4 x i8], [4 x i8]* %62, i32 0, i32 3
  %64 = load i8, i8* %63, align 1
  store i8 %64, i8* %1, align 1
  %65 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %66 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %65, i32 0, i32 3
  %67 = getelementptr inbounds [4 x i8], [4 x i8]* %66, i32 0, i32 3
  %68 = load i8, i8* %67, align 1
  %69 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %70 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %69, i32 0, i32 0
  %71 = getelementptr inbounds [4 x i8], [4 x i8]* %70, i32 0, i32 3
  store i8 %68, i8* %71, align 1
  %72 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %73 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %72, i32 0, i32 2
  %74 = getelementptr inbounds [4 x i8], [4 x i8]* %73, i32 0, i32 3
  %75 = load i8, i8* %74, align 1
  %76 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %77 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %76, i32 0, i32 3
  %78 = getelementptr inbounds [4 x i8], [4 x i8]* %77, i32 0, i32 3
  store i8 %75, i8* %78, align 1
  %79 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %80 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %79, i32 0, i32 1
  %81 = getelementptr inbounds [4 x i8], [4 x i8]* %80, i32 0, i32 3
  %82 = load i8, i8* %81, align 1
  %83 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %84 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %83, i32 0, i32 2
  %85 = getelementptr inbounds [4 x i8], [4 x i8]* %84, i32 0, i32 3
  store i8 %82, i8* %85, align 1
  %86 = load i8, i8* %1, align 1
  %87 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %88 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %87, i32 0, i32 1
  %89 = getelementptr inbounds [4 x i8], [4 x i8]* %88, i32 0, i32 3
  store i8 %86, i8* %89, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal void @MixColumns() #0 {
  %1 = alloca i8, align 1
  %2 = alloca i8, align 1
  %3 = alloca i8, align 1
  %4 = alloca i8, align 1
  store i8 0, i8* %1, align 1
  br label %5

; <label>:5:                                      ; preds = %171, %0
  %6 = load i8, i8* %1, align 1
  %7 = zext i8 %6 to i32
  %8 = icmp slt i32 %7, 4
  br i1 %8, label %9, label %174

; <label>:9:                                      ; preds = %5
  %10 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %11 = load i8, i8* %1, align 1
  %12 = zext i8 %11 to i32
  %13 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %10, i32 0, i32 %12
  %14 = getelementptr inbounds [4 x i8], [4 x i8]* %13, i32 0, i32 0
  %15 = load i8, i8* %14, align 1
  store i8 %15, i8* %4, align 1
  %16 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %17 = load i8, i8* %1, align 1
  %18 = zext i8 %17 to i32
  %19 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %16, i32 0, i32 %18
  %20 = getelementptr inbounds [4 x i8], [4 x i8]* %19, i32 0, i32 0
  %21 = load i8, i8* %20, align 1
  %22 = zext i8 %21 to i32
  %23 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %24 = load i8, i8* %1, align 1
  %25 = zext i8 %24 to i32
  %26 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %23, i32 0, i32 %25
  %27 = getelementptr inbounds [4 x i8], [4 x i8]* %26, i32 0, i32 1
  %28 = load i8, i8* %27, align 1
  %29 = zext i8 %28 to i32
  %30 = xor i32 %22, %29
  %31 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %32 = load i8, i8* %1, align 1
  %33 = zext i8 %32 to i32
  %34 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %31, i32 0, i32 %33
  %35 = getelementptr inbounds [4 x i8], [4 x i8]* %34, i32 0, i32 2
  %36 = load i8, i8* %35, align 1
  %37 = zext i8 %36 to i32
  %38 = xor i32 %30, %37
  %39 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %40 = load i8, i8* %1, align 1
  %41 = zext i8 %40 to i32
  %42 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %39, i32 0, i32 %41
  %43 = getelementptr inbounds [4 x i8], [4 x i8]* %42, i32 0, i32 3
  %44 = load i8, i8* %43, align 1
  %45 = zext i8 %44 to i32
  %46 = xor i32 %38, %45
  %47 = trunc i32 %46 to i8
  store i8 %47, i8* %2, align 1
  %48 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %49 = load i8, i8* %1, align 1
  %50 = zext i8 %49 to i32
  %51 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %48, i32 0, i32 %50
  %52 = getelementptr inbounds [4 x i8], [4 x i8]* %51, i32 0, i32 0
  %53 = load i8, i8* %52, align 1
  %54 = zext i8 %53 to i32
  %55 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %56 = load i8, i8* %1, align 1
  %57 = zext i8 %56 to i32
  %58 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %55, i32 0, i32 %57
  %59 = getelementptr inbounds [4 x i8], [4 x i8]* %58, i32 0, i32 1
  %60 = load i8, i8* %59, align 1
  %61 = zext i8 %60 to i32
  %62 = xor i32 %54, %61
  %63 = trunc i32 %62 to i8
  store i8 %63, i8* %3, align 1
  %64 = load i8, i8* %3, align 1
  %65 = call zeroext i8 @xtime(i8 zeroext %64)
  store i8 %65, i8* %3, align 1
  %66 = load i8, i8* %3, align 1
  %67 = zext i8 %66 to i32
  %68 = load i8, i8* %2, align 1
  %69 = zext i8 %68 to i32
  %70 = xor i32 %67, %69
  %71 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %72 = load i8, i8* %1, align 1
  %73 = zext i8 %72 to i32
  %74 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %71, i32 0, i32 %73
  %75 = getelementptr inbounds [4 x i8], [4 x i8]* %74, i32 0, i32 0
  %76 = load i8, i8* %75, align 1
  %77 = zext i8 %76 to i32
  %78 = xor i32 %77, %70
  %79 = trunc i32 %78 to i8
  store i8 %79, i8* %75, align 1
  %80 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %81 = load i8, i8* %1, align 1
  %82 = zext i8 %81 to i32
  %83 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %80, i32 0, i32 %82
  %84 = getelementptr inbounds [4 x i8], [4 x i8]* %83, i32 0, i32 1
  %85 = load i8, i8* %84, align 1
  %86 = zext i8 %85 to i32
  %87 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %88 = load i8, i8* %1, align 1
  %89 = zext i8 %88 to i32
  %90 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %87, i32 0, i32 %89
  %91 = getelementptr inbounds [4 x i8], [4 x i8]* %90, i32 0, i32 2
  %92 = load i8, i8* %91, align 1
  %93 = zext i8 %92 to i32
  %94 = xor i32 %86, %93
  %95 = trunc i32 %94 to i8
  store i8 %95, i8* %3, align 1
  %96 = load i8, i8* %3, align 1
  %97 = call zeroext i8 @xtime(i8 zeroext %96)
  store i8 %97, i8* %3, align 1
  %98 = load i8, i8* %3, align 1
  %99 = zext i8 %98 to i32
  %100 = load i8, i8* %2, align 1
  %101 = zext i8 %100 to i32
  %102 = xor i32 %99, %101
  %103 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %104 = load i8, i8* %1, align 1
  %105 = zext i8 %104 to i32
  %106 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %103, i32 0, i32 %105
  %107 = getelementptr inbounds [4 x i8], [4 x i8]* %106, i32 0, i32 1
  %108 = load i8, i8* %107, align 1
  %109 = zext i8 %108 to i32
  %110 = xor i32 %109, %102
  %111 = trunc i32 %110 to i8
  store i8 %111, i8* %107, align 1
  %112 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %113 = load i8, i8* %1, align 1
  %114 = zext i8 %113 to i32
  %115 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %112, i32 0, i32 %114
  %116 = getelementptr inbounds [4 x i8], [4 x i8]* %115, i32 0, i32 2
  %117 = load i8, i8* %116, align 1
  %118 = zext i8 %117 to i32
  %119 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %120 = load i8, i8* %1, align 1
  %121 = zext i8 %120 to i32
  %122 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %119, i32 0, i32 %121
  %123 = getelementptr inbounds [4 x i8], [4 x i8]* %122, i32 0, i32 3
  %124 = load i8, i8* %123, align 1
  %125 = zext i8 %124 to i32
  %126 = xor i32 %118, %125
  %127 = trunc i32 %126 to i8
  store i8 %127, i8* %3, align 1
  %128 = load i8, i8* %3, align 1
  %129 = call zeroext i8 @xtime(i8 zeroext %128)
  store i8 %129, i8* %3, align 1
  %130 = load i8, i8* %3, align 1
  %131 = zext i8 %130 to i32
  %132 = load i8, i8* %2, align 1
  %133 = zext i8 %132 to i32
  %134 = xor i32 %131, %133
  %135 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %136 = load i8, i8* %1, align 1
  %137 = zext i8 %136 to i32
  %138 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %135, i32 0, i32 %137
  %139 = getelementptr inbounds [4 x i8], [4 x i8]* %138, i32 0, i32 2
  %140 = load i8, i8* %139, align 1
  %141 = zext i8 %140 to i32
  %142 = xor i32 %141, %134
  %143 = trunc i32 %142 to i8
  store i8 %143, i8* %139, align 1
  %144 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %145 = load i8, i8* %1, align 1
  %146 = zext i8 %145 to i32
  %147 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %144, i32 0, i32 %146
  %148 = getelementptr inbounds [4 x i8], [4 x i8]* %147, i32 0, i32 3
  %149 = load i8, i8* %148, align 1
  %150 = zext i8 %149 to i32
  %151 = load i8, i8* %4, align 1
  %152 = zext i8 %151 to i32
  %153 = xor i32 %150, %152
  %154 = trunc i32 %153 to i8
  store i8 %154, i8* %3, align 1
  %155 = load i8, i8* %3, align 1
  %156 = call zeroext i8 @xtime(i8 zeroext %155)
  store i8 %156, i8* %3, align 1
  %157 = load i8, i8* %3, align 1
  %158 = zext i8 %157 to i32
  %159 = load i8, i8* %2, align 1
  %160 = zext i8 %159 to i32
  %161 = xor i32 %158, %160
  %162 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %163 = load i8, i8* %1, align 1
  %164 = zext i8 %163 to i32
  %165 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %162, i32 0, i32 %164
  %166 = getelementptr inbounds [4 x i8], [4 x i8]* %165, i32 0, i32 3
  %167 = load i8, i8* %166, align 1
  %168 = zext i8 %167 to i32
  %169 = xor i32 %168, %161
  %170 = trunc i32 %169 to i8
  store i8 %170, i8* %166, align 1
  br label %171

; <label>:171:                                    ; preds = %9
  %172 = load i8, i8* %1, align 1
  %173 = add i8 %172, 1
  store i8 %173, i8* %1, align 1
  br label %5

; <label>:174:                                    ; preds = %5
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal zeroext i8 @xtime(i8 zeroext) #0 {
  %2 = alloca i8, align 1
  store i8 %0, i8* %2, align 1
  %3 = load i8, i8* %2, align 1
  %4 = zext i8 %3 to i32
  %5 = shl i32 %4, 1
  %6 = load i8, i8* %2, align 1
  %7 = zext i8 %6 to i32
  %8 = ashr i32 %7, 7
  %9 = and i32 %8, 1
  %10 = mul nsw i32 %9, 27
  %11 = xor i32 %5, %10
  %12 = trunc i32 %11 to i8
  ret i8 %12
}

; Function Attrs: noinline nounwind optnone
define internal void @InvShiftRows() #0 {
  %1 = alloca i8, align 1
  %2 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %3 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %2, i32 0, i32 3
  %4 = getelementptr inbounds [4 x i8], [4 x i8]* %3, i32 0, i32 1
  %5 = load i8, i8* %4, align 1
  store i8 %5, i8* %1, align 1
  %6 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %7 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %6, i32 0, i32 2
  %8 = getelementptr inbounds [4 x i8], [4 x i8]* %7, i32 0, i32 1
  %9 = load i8, i8* %8, align 1
  %10 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %11 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %10, i32 0, i32 3
  %12 = getelementptr inbounds [4 x i8], [4 x i8]* %11, i32 0, i32 1
  store i8 %9, i8* %12, align 1
  %13 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %14 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %13, i32 0, i32 1
  %15 = getelementptr inbounds [4 x i8], [4 x i8]* %14, i32 0, i32 1
  %16 = load i8, i8* %15, align 1
  %17 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %18 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %17, i32 0, i32 2
  %19 = getelementptr inbounds [4 x i8], [4 x i8]* %18, i32 0, i32 1
  store i8 %16, i8* %19, align 1
  %20 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %21 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %20, i32 0, i32 0
  %22 = getelementptr inbounds [4 x i8], [4 x i8]* %21, i32 0, i32 1
  %23 = load i8, i8* %22, align 1
  %24 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %25 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %24, i32 0, i32 1
  %26 = getelementptr inbounds [4 x i8], [4 x i8]* %25, i32 0, i32 1
  store i8 %23, i8* %26, align 1
  %27 = load i8, i8* %1, align 1
  %28 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %29 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %28, i32 0, i32 0
  %30 = getelementptr inbounds [4 x i8], [4 x i8]* %29, i32 0, i32 1
  store i8 %27, i8* %30, align 1
  %31 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %32 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %31, i32 0, i32 0
  %33 = getelementptr inbounds [4 x i8], [4 x i8]* %32, i32 0, i32 2
  %34 = load i8, i8* %33, align 1
  store i8 %34, i8* %1, align 1
  %35 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %36 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %35, i32 0, i32 2
  %37 = getelementptr inbounds [4 x i8], [4 x i8]* %36, i32 0, i32 2
  %38 = load i8, i8* %37, align 1
  %39 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %40 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %39, i32 0, i32 0
  %41 = getelementptr inbounds [4 x i8], [4 x i8]* %40, i32 0, i32 2
  store i8 %38, i8* %41, align 1
  %42 = load i8, i8* %1, align 1
  %43 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %44 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %43, i32 0, i32 2
  %45 = getelementptr inbounds [4 x i8], [4 x i8]* %44, i32 0, i32 2
  store i8 %42, i8* %45, align 1
  %46 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %47 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %46, i32 0, i32 1
  %48 = getelementptr inbounds [4 x i8], [4 x i8]* %47, i32 0, i32 2
  %49 = load i8, i8* %48, align 1
  store i8 %49, i8* %1, align 1
  %50 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %51 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %50, i32 0, i32 3
  %52 = getelementptr inbounds [4 x i8], [4 x i8]* %51, i32 0, i32 2
  %53 = load i8, i8* %52, align 1
  %54 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %55 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %54, i32 0, i32 1
  %56 = getelementptr inbounds [4 x i8], [4 x i8]* %55, i32 0, i32 2
  store i8 %53, i8* %56, align 1
  %57 = load i8, i8* %1, align 1
  %58 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %59 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %58, i32 0, i32 3
  %60 = getelementptr inbounds [4 x i8], [4 x i8]* %59, i32 0, i32 2
  store i8 %57, i8* %60, align 1
  %61 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %62 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %61, i32 0, i32 0
  %63 = getelementptr inbounds [4 x i8], [4 x i8]* %62, i32 0, i32 3
  %64 = load i8, i8* %63, align 1
  store i8 %64, i8* %1, align 1
  %65 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %66 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %65, i32 0, i32 1
  %67 = getelementptr inbounds [4 x i8], [4 x i8]* %66, i32 0, i32 3
  %68 = load i8, i8* %67, align 1
  %69 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %70 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %69, i32 0, i32 0
  %71 = getelementptr inbounds [4 x i8], [4 x i8]* %70, i32 0, i32 3
  store i8 %68, i8* %71, align 1
  %72 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %73 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %72, i32 0, i32 2
  %74 = getelementptr inbounds [4 x i8], [4 x i8]* %73, i32 0, i32 3
  %75 = load i8, i8* %74, align 1
  %76 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %77 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %76, i32 0, i32 1
  %78 = getelementptr inbounds [4 x i8], [4 x i8]* %77, i32 0, i32 3
  store i8 %75, i8* %78, align 1
  %79 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %80 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %79, i32 0, i32 3
  %81 = getelementptr inbounds [4 x i8], [4 x i8]* %80, i32 0, i32 3
  %82 = load i8, i8* %81, align 1
  %83 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %84 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %83, i32 0, i32 2
  %85 = getelementptr inbounds [4 x i8], [4 x i8]* %84, i32 0, i32 3
  store i8 %82, i8* %85, align 1
  %86 = load i8, i8* %1, align 1
  %87 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %88 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %87, i32 0, i32 3
  %89 = getelementptr inbounds [4 x i8], [4 x i8]* %88, i32 0, i32 3
  store i8 %86, i8* %89, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal void @InvSubBytes() #0 {
  %1 = alloca i8, align 1
  %2 = alloca i8, align 1
  store i8 0, i8* %1, align 1
  br label %3

; <label>:3:                                      ; preds = %33, %0
  %4 = load i8, i8* %1, align 1
  %5 = zext i8 %4 to i32
  %6 = icmp slt i32 %5, 4
  br i1 %6, label %7, label %36

; <label>:7:                                      ; preds = %3
  store i8 0, i8* %2, align 1
  br label %8

; <label>:8:                                      ; preds = %29, %7
  %9 = load i8, i8* %2, align 1
  %10 = zext i8 %9 to i32
  %11 = icmp slt i32 %10, 4
  br i1 %11, label %12, label %32

; <label>:12:                                     ; preds = %8
  %13 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %14 = load i8, i8* %2, align 1
  %15 = zext i8 %14 to i32
  %16 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %13, i32 0, i32 %15
  %17 = load i8, i8* %1, align 1
  %18 = zext i8 %17 to i32
  %19 = getelementptr inbounds [4 x i8], [4 x i8]* %16, i32 0, i32 %18
  %20 = load i8, i8* %19, align 1
  %21 = call zeroext i8 @getSBoxInvert(i8 zeroext %20)
  %22 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %23 = load i8, i8* %2, align 1
  %24 = zext i8 %23 to i32
  %25 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %22, i32 0, i32 %24
  %26 = load i8, i8* %1, align 1
  %27 = zext i8 %26 to i32
  %28 = getelementptr inbounds [4 x i8], [4 x i8]* %25, i32 0, i32 %27
  store i8 %21, i8* %28, align 1
  br label %29

; <label>:29:                                     ; preds = %12
  %30 = load i8, i8* %2, align 1
  %31 = add i8 %30, 1
  store i8 %31, i8* %2, align 1
  br label %8

; <label>:32:                                     ; preds = %8
  br label %33

; <label>:33:                                     ; preds = %32
  %34 = load i8, i8* %1, align 1
  %35 = add i8 %34, 1
  store i8 %35, i8* %1, align 1
  br label %3

; <label>:36:                                     ; preds = %3
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal void @InvMixColumns() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i8, align 1
  %3 = alloca i8, align 1
  %4 = alloca i8, align 1
  %5 = alloca i8, align 1
  store i32 0, i32* %1, align 4
  br label %6

; <label>:6:                                      ; preds = %526, %0
  %7 = load i32, i32* %1, align 4
  %8 = icmp slt i32 %7, 4
  br i1 %8, label %9, label %529

; <label>:9:                                      ; preds = %6
  %10 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %11 = load i32, i32* %1, align 4
  %12 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %10, i32 0, i32 %11
  %13 = getelementptr inbounds [4 x i8], [4 x i8]* %12, i32 0, i32 0
  %14 = load i8, i8* %13, align 1
  store i8 %14, i8* %2, align 1
  %15 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %16 = load i32, i32* %1, align 4
  %17 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %15, i32 0, i32 %16
  %18 = getelementptr inbounds [4 x i8], [4 x i8]* %17, i32 0, i32 1
  %19 = load i8, i8* %18, align 1
  store i8 %19, i8* %3, align 1
  %20 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %21 = load i32, i32* %1, align 4
  %22 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %20, i32 0, i32 %21
  %23 = getelementptr inbounds [4 x i8], [4 x i8]* %22, i32 0, i32 2
  %24 = load i8, i8* %23, align 1
  store i8 %24, i8* %4, align 1
  %25 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %26 = load i32, i32* %1, align 4
  %27 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %25, i32 0, i32 %26
  %28 = getelementptr inbounds [4 x i8], [4 x i8]* %27, i32 0, i32 3
  %29 = load i8, i8* %28, align 1
  store i8 %29, i8* %5, align 1
  %30 = load i8, i8* %2, align 1
  %31 = zext i8 %30 to i32
  %32 = mul nsw i32 0, %31
  %33 = load i8, i8* %2, align 1
  %34 = call zeroext i8 @xtime(i8 zeroext %33)
  %35 = zext i8 %34 to i32
  %36 = mul nsw i32 1, %35
  %37 = xor i32 %32, %36
  %38 = load i8, i8* %2, align 1
  %39 = call zeroext i8 @xtime(i8 zeroext %38)
  %40 = call zeroext i8 @xtime(i8 zeroext %39)
  %41 = zext i8 %40 to i32
  %42 = mul nsw i32 1, %41
  %43 = xor i32 %37, %42
  %44 = load i8, i8* %2, align 1
  %45 = call zeroext i8 @xtime(i8 zeroext %44)
  %46 = call zeroext i8 @xtime(i8 zeroext %45)
  %47 = call zeroext i8 @xtime(i8 zeroext %46)
  %48 = zext i8 %47 to i32
  %49 = mul nsw i32 1, %48
  %50 = xor i32 %43, %49
  %51 = load i8, i8* %2, align 1
  %52 = call zeroext i8 @xtime(i8 zeroext %51)
  %53 = call zeroext i8 @xtime(i8 zeroext %52)
  %54 = call zeroext i8 @xtime(i8 zeroext %53)
  %55 = call zeroext i8 @xtime(i8 zeroext %54)
  %56 = zext i8 %55 to i32
  %57 = mul nsw i32 0, %56
  %58 = xor i32 %50, %57
  %59 = load i8, i8* %3, align 1
  %60 = zext i8 %59 to i32
  %61 = mul nsw i32 1, %60
  %62 = load i8, i8* %3, align 1
  %63 = call zeroext i8 @xtime(i8 zeroext %62)
  %64 = zext i8 %63 to i32
  %65 = mul nsw i32 1, %64
  %66 = xor i32 %61, %65
  %67 = load i8, i8* %3, align 1
  %68 = call zeroext i8 @xtime(i8 zeroext %67)
  %69 = call zeroext i8 @xtime(i8 zeroext %68)
  %70 = zext i8 %69 to i32
  %71 = mul nsw i32 0, %70
  %72 = xor i32 %66, %71
  %73 = load i8, i8* %3, align 1
  %74 = call zeroext i8 @xtime(i8 zeroext %73)
  %75 = call zeroext i8 @xtime(i8 zeroext %74)
  %76 = call zeroext i8 @xtime(i8 zeroext %75)
  %77 = zext i8 %76 to i32
  %78 = mul nsw i32 1, %77
  %79 = xor i32 %72, %78
  %80 = load i8, i8* %3, align 1
  %81 = call zeroext i8 @xtime(i8 zeroext %80)
  %82 = call zeroext i8 @xtime(i8 zeroext %81)
  %83 = call zeroext i8 @xtime(i8 zeroext %82)
  %84 = call zeroext i8 @xtime(i8 zeroext %83)
  %85 = zext i8 %84 to i32
  %86 = mul nsw i32 0, %85
  %87 = xor i32 %79, %86
  %88 = xor i32 %58, %87
  %89 = load i8, i8* %4, align 1
  %90 = zext i8 %89 to i32
  %91 = mul nsw i32 1, %90
  %92 = load i8, i8* %4, align 1
  %93 = call zeroext i8 @xtime(i8 zeroext %92)
  %94 = zext i8 %93 to i32
  %95 = mul nsw i32 0, %94
  %96 = xor i32 %91, %95
  %97 = load i8, i8* %4, align 1
  %98 = call zeroext i8 @xtime(i8 zeroext %97)
  %99 = call zeroext i8 @xtime(i8 zeroext %98)
  %100 = zext i8 %99 to i32
  %101 = mul nsw i32 1, %100
  %102 = xor i32 %96, %101
  %103 = load i8, i8* %4, align 1
  %104 = call zeroext i8 @xtime(i8 zeroext %103)
  %105 = call zeroext i8 @xtime(i8 zeroext %104)
  %106 = call zeroext i8 @xtime(i8 zeroext %105)
  %107 = zext i8 %106 to i32
  %108 = mul nsw i32 1, %107
  %109 = xor i32 %102, %108
  %110 = load i8, i8* %4, align 1
  %111 = call zeroext i8 @xtime(i8 zeroext %110)
  %112 = call zeroext i8 @xtime(i8 zeroext %111)
  %113 = call zeroext i8 @xtime(i8 zeroext %112)
  %114 = call zeroext i8 @xtime(i8 zeroext %113)
  %115 = zext i8 %114 to i32
  %116 = mul nsw i32 0, %115
  %117 = xor i32 %109, %116
  %118 = xor i32 %88, %117
  %119 = load i8, i8* %5, align 1
  %120 = zext i8 %119 to i32
  %121 = mul nsw i32 1, %120
  %122 = load i8, i8* %5, align 1
  %123 = call zeroext i8 @xtime(i8 zeroext %122)
  %124 = zext i8 %123 to i32
  %125 = mul nsw i32 0, %124
  %126 = xor i32 %121, %125
  %127 = load i8, i8* %5, align 1
  %128 = call zeroext i8 @xtime(i8 zeroext %127)
  %129 = call zeroext i8 @xtime(i8 zeroext %128)
  %130 = zext i8 %129 to i32
  %131 = mul nsw i32 0, %130
  %132 = xor i32 %126, %131
  %133 = load i8, i8* %5, align 1
  %134 = call zeroext i8 @xtime(i8 zeroext %133)
  %135 = call zeroext i8 @xtime(i8 zeroext %134)
  %136 = call zeroext i8 @xtime(i8 zeroext %135)
  %137 = zext i8 %136 to i32
  %138 = mul nsw i32 1, %137
  %139 = xor i32 %132, %138
  %140 = load i8, i8* %5, align 1
  %141 = call zeroext i8 @xtime(i8 zeroext %140)
  %142 = call zeroext i8 @xtime(i8 zeroext %141)
  %143 = call zeroext i8 @xtime(i8 zeroext %142)
  %144 = call zeroext i8 @xtime(i8 zeroext %143)
  %145 = zext i8 %144 to i32
  %146 = mul nsw i32 0, %145
  %147 = xor i32 %139, %146
  %148 = xor i32 %118, %147
  %149 = trunc i32 %148 to i8
  %150 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %151 = load i32, i32* %1, align 4
  %152 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %150, i32 0, i32 %151
  %153 = getelementptr inbounds [4 x i8], [4 x i8]* %152, i32 0, i32 0
  store i8 %149, i8* %153, align 1
  %154 = load i8, i8* %2, align 1
  %155 = zext i8 %154 to i32
  %156 = mul nsw i32 1, %155
  %157 = load i8, i8* %2, align 1
  %158 = call zeroext i8 @xtime(i8 zeroext %157)
  %159 = zext i8 %158 to i32
  %160 = mul nsw i32 0, %159
  %161 = xor i32 %156, %160
  %162 = load i8, i8* %2, align 1
  %163 = call zeroext i8 @xtime(i8 zeroext %162)
  %164 = call zeroext i8 @xtime(i8 zeroext %163)
  %165 = zext i8 %164 to i32
  %166 = mul nsw i32 0, %165
  %167 = xor i32 %161, %166
  %168 = load i8, i8* %2, align 1
  %169 = call zeroext i8 @xtime(i8 zeroext %168)
  %170 = call zeroext i8 @xtime(i8 zeroext %169)
  %171 = call zeroext i8 @xtime(i8 zeroext %170)
  %172 = zext i8 %171 to i32
  %173 = mul nsw i32 1, %172
  %174 = xor i32 %167, %173
  %175 = load i8, i8* %2, align 1
  %176 = call zeroext i8 @xtime(i8 zeroext %175)
  %177 = call zeroext i8 @xtime(i8 zeroext %176)
  %178 = call zeroext i8 @xtime(i8 zeroext %177)
  %179 = call zeroext i8 @xtime(i8 zeroext %178)
  %180 = zext i8 %179 to i32
  %181 = mul nsw i32 0, %180
  %182 = xor i32 %174, %181
  %183 = load i8, i8* %3, align 1
  %184 = zext i8 %183 to i32
  %185 = mul nsw i32 0, %184
  %186 = load i8, i8* %3, align 1
  %187 = call zeroext i8 @xtime(i8 zeroext %186)
  %188 = zext i8 %187 to i32
  %189 = mul nsw i32 1, %188
  %190 = xor i32 %185, %189
  %191 = load i8, i8* %3, align 1
  %192 = call zeroext i8 @xtime(i8 zeroext %191)
  %193 = call zeroext i8 @xtime(i8 zeroext %192)
  %194 = zext i8 %193 to i32
  %195 = mul nsw i32 1, %194
  %196 = xor i32 %190, %195
  %197 = load i8, i8* %3, align 1
  %198 = call zeroext i8 @xtime(i8 zeroext %197)
  %199 = call zeroext i8 @xtime(i8 zeroext %198)
  %200 = call zeroext i8 @xtime(i8 zeroext %199)
  %201 = zext i8 %200 to i32
  %202 = mul nsw i32 1, %201
  %203 = xor i32 %196, %202
  %204 = load i8, i8* %3, align 1
  %205 = call zeroext i8 @xtime(i8 zeroext %204)
  %206 = call zeroext i8 @xtime(i8 zeroext %205)
  %207 = call zeroext i8 @xtime(i8 zeroext %206)
  %208 = call zeroext i8 @xtime(i8 zeroext %207)
  %209 = zext i8 %208 to i32
  %210 = mul nsw i32 0, %209
  %211 = xor i32 %203, %210
  %212 = xor i32 %182, %211
  %213 = load i8, i8* %4, align 1
  %214 = zext i8 %213 to i32
  %215 = mul nsw i32 1, %214
  %216 = load i8, i8* %4, align 1
  %217 = call zeroext i8 @xtime(i8 zeroext %216)
  %218 = zext i8 %217 to i32
  %219 = mul nsw i32 1, %218
  %220 = xor i32 %215, %219
  %221 = load i8, i8* %4, align 1
  %222 = call zeroext i8 @xtime(i8 zeroext %221)
  %223 = call zeroext i8 @xtime(i8 zeroext %222)
  %224 = zext i8 %223 to i32
  %225 = mul nsw i32 0, %224
  %226 = xor i32 %220, %225
  %227 = load i8, i8* %4, align 1
  %228 = call zeroext i8 @xtime(i8 zeroext %227)
  %229 = call zeroext i8 @xtime(i8 zeroext %228)
  %230 = call zeroext i8 @xtime(i8 zeroext %229)
  %231 = zext i8 %230 to i32
  %232 = mul nsw i32 1, %231
  %233 = xor i32 %226, %232
  %234 = load i8, i8* %4, align 1
  %235 = call zeroext i8 @xtime(i8 zeroext %234)
  %236 = call zeroext i8 @xtime(i8 zeroext %235)
  %237 = call zeroext i8 @xtime(i8 zeroext %236)
  %238 = call zeroext i8 @xtime(i8 zeroext %237)
  %239 = zext i8 %238 to i32
  %240 = mul nsw i32 0, %239
  %241 = xor i32 %233, %240
  %242 = xor i32 %212, %241
  %243 = load i8, i8* %5, align 1
  %244 = zext i8 %243 to i32
  %245 = mul nsw i32 1, %244
  %246 = load i8, i8* %5, align 1
  %247 = call zeroext i8 @xtime(i8 zeroext %246)
  %248 = zext i8 %247 to i32
  %249 = mul nsw i32 0, %248
  %250 = xor i32 %245, %249
  %251 = load i8, i8* %5, align 1
  %252 = call zeroext i8 @xtime(i8 zeroext %251)
  %253 = call zeroext i8 @xtime(i8 zeroext %252)
  %254 = zext i8 %253 to i32
  %255 = mul nsw i32 1, %254
  %256 = xor i32 %250, %255
  %257 = load i8, i8* %5, align 1
  %258 = call zeroext i8 @xtime(i8 zeroext %257)
  %259 = call zeroext i8 @xtime(i8 zeroext %258)
  %260 = call zeroext i8 @xtime(i8 zeroext %259)
  %261 = zext i8 %260 to i32
  %262 = mul nsw i32 1, %261
  %263 = xor i32 %256, %262
  %264 = load i8, i8* %5, align 1
  %265 = call zeroext i8 @xtime(i8 zeroext %264)
  %266 = call zeroext i8 @xtime(i8 zeroext %265)
  %267 = call zeroext i8 @xtime(i8 zeroext %266)
  %268 = call zeroext i8 @xtime(i8 zeroext %267)
  %269 = zext i8 %268 to i32
  %270 = mul nsw i32 0, %269
  %271 = xor i32 %263, %270
  %272 = xor i32 %242, %271
  %273 = trunc i32 %272 to i8
  %274 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %275 = load i32, i32* %1, align 4
  %276 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %274, i32 0, i32 %275
  %277 = getelementptr inbounds [4 x i8], [4 x i8]* %276, i32 0, i32 1
  store i8 %273, i8* %277, align 1
  %278 = load i8, i8* %2, align 1
  %279 = zext i8 %278 to i32
  %280 = mul nsw i32 1, %279
  %281 = load i8, i8* %2, align 1
  %282 = call zeroext i8 @xtime(i8 zeroext %281)
  %283 = zext i8 %282 to i32
  %284 = mul nsw i32 0, %283
  %285 = xor i32 %280, %284
  %286 = load i8, i8* %2, align 1
  %287 = call zeroext i8 @xtime(i8 zeroext %286)
  %288 = call zeroext i8 @xtime(i8 zeroext %287)
  %289 = zext i8 %288 to i32
  %290 = mul nsw i32 1, %289
  %291 = xor i32 %285, %290
  %292 = load i8, i8* %2, align 1
  %293 = call zeroext i8 @xtime(i8 zeroext %292)
  %294 = call zeroext i8 @xtime(i8 zeroext %293)
  %295 = call zeroext i8 @xtime(i8 zeroext %294)
  %296 = zext i8 %295 to i32
  %297 = mul nsw i32 1, %296
  %298 = xor i32 %291, %297
  %299 = load i8, i8* %2, align 1
  %300 = call zeroext i8 @xtime(i8 zeroext %299)
  %301 = call zeroext i8 @xtime(i8 zeroext %300)
  %302 = call zeroext i8 @xtime(i8 zeroext %301)
  %303 = call zeroext i8 @xtime(i8 zeroext %302)
  %304 = zext i8 %303 to i32
  %305 = mul nsw i32 0, %304
  %306 = xor i32 %298, %305
  %307 = load i8, i8* %3, align 1
  %308 = zext i8 %307 to i32
  %309 = mul nsw i32 1, %308
  %310 = load i8, i8* %3, align 1
  %311 = call zeroext i8 @xtime(i8 zeroext %310)
  %312 = zext i8 %311 to i32
  %313 = mul nsw i32 0, %312
  %314 = xor i32 %309, %313
  %315 = load i8, i8* %3, align 1
  %316 = call zeroext i8 @xtime(i8 zeroext %315)
  %317 = call zeroext i8 @xtime(i8 zeroext %316)
  %318 = zext i8 %317 to i32
  %319 = mul nsw i32 0, %318
  %320 = xor i32 %314, %319
  %321 = load i8, i8* %3, align 1
  %322 = call zeroext i8 @xtime(i8 zeroext %321)
  %323 = call zeroext i8 @xtime(i8 zeroext %322)
  %324 = call zeroext i8 @xtime(i8 zeroext %323)
  %325 = zext i8 %324 to i32
  %326 = mul nsw i32 1, %325
  %327 = xor i32 %320, %326
  %328 = load i8, i8* %3, align 1
  %329 = call zeroext i8 @xtime(i8 zeroext %328)
  %330 = call zeroext i8 @xtime(i8 zeroext %329)
  %331 = call zeroext i8 @xtime(i8 zeroext %330)
  %332 = call zeroext i8 @xtime(i8 zeroext %331)
  %333 = zext i8 %332 to i32
  %334 = mul nsw i32 0, %333
  %335 = xor i32 %327, %334
  %336 = xor i32 %306, %335
  %337 = load i8, i8* %4, align 1
  %338 = zext i8 %337 to i32
  %339 = mul nsw i32 0, %338
  %340 = load i8, i8* %4, align 1
  %341 = call zeroext i8 @xtime(i8 zeroext %340)
  %342 = zext i8 %341 to i32
  %343 = mul nsw i32 1, %342
  %344 = xor i32 %339, %343
  %345 = load i8, i8* %4, align 1
  %346 = call zeroext i8 @xtime(i8 zeroext %345)
  %347 = call zeroext i8 @xtime(i8 zeroext %346)
  %348 = zext i8 %347 to i32
  %349 = mul nsw i32 1, %348
  %350 = xor i32 %344, %349
  %351 = load i8, i8* %4, align 1
  %352 = call zeroext i8 @xtime(i8 zeroext %351)
  %353 = call zeroext i8 @xtime(i8 zeroext %352)
  %354 = call zeroext i8 @xtime(i8 zeroext %353)
  %355 = zext i8 %354 to i32
  %356 = mul nsw i32 1, %355
  %357 = xor i32 %350, %356
  %358 = load i8, i8* %4, align 1
  %359 = call zeroext i8 @xtime(i8 zeroext %358)
  %360 = call zeroext i8 @xtime(i8 zeroext %359)
  %361 = call zeroext i8 @xtime(i8 zeroext %360)
  %362 = call zeroext i8 @xtime(i8 zeroext %361)
  %363 = zext i8 %362 to i32
  %364 = mul nsw i32 0, %363
  %365 = xor i32 %357, %364
  %366 = xor i32 %336, %365
  %367 = load i8, i8* %5, align 1
  %368 = zext i8 %367 to i32
  %369 = mul nsw i32 1, %368
  %370 = load i8, i8* %5, align 1
  %371 = call zeroext i8 @xtime(i8 zeroext %370)
  %372 = zext i8 %371 to i32
  %373 = mul nsw i32 1, %372
  %374 = xor i32 %369, %373
  %375 = load i8, i8* %5, align 1
  %376 = call zeroext i8 @xtime(i8 zeroext %375)
  %377 = call zeroext i8 @xtime(i8 zeroext %376)
  %378 = zext i8 %377 to i32
  %379 = mul nsw i32 0, %378
  %380 = xor i32 %374, %379
  %381 = load i8, i8* %5, align 1
  %382 = call zeroext i8 @xtime(i8 zeroext %381)
  %383 = call zeroext i8 @xtime(i8 zeroext %382)
  %384 = call zeroext i8 @xtime(i8 zeroext %383)
  %385 = zext i8 %384 to i32
  %386 = mul nsw i32 1, %385
  %387 = xor i32 %380, %386
  %388 = load i8, i8* %5, align 1
  %389 = call zeroext i8 @xtime(i8 zeroext %388)
  %390 = call zeroext i8 @xtime(i8 zeroext %389)
  %391 = call zeroext i8 @xtime(i8 zeroext %390)
  %392 = call zeroext i8 @xtime(i8 zeroext %391)
  %393 = zext i8 %392 to i32
  %394 = mul nsw i32 0, %393
  %395 = xor i32 %387, %394
  %396 = xor i32 %366, %395
  %397 = trunc i32 %396 to i8
  %398 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %399 = load i32, i32* %1, align 4
  %400 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %398, i32 0, i32 %399
  %401 = getelementptr inbounds [4 x i8], [4 x i8]* %400, i32 0, i32 2
  store i8 %397, i8* %401, align 1
  %402 = load i8, i8* %2, align 1
  %403 = zext i8 %402 to i32
  %404 = mul nsw i32 1, %403
  %405 = load i8, i8* %2, align 1
  %406 = call zeroext i8 @xtime(i8 zeroext %405)
  %407 = zext i8 %406 to i32
  %408 = mul nsw i32 1, %407
  %409 = xor i32 %404, %408
  %410 = load i8, i8* %2, align 1
  %411 = call zeroext i8 @xtime(i8 zeroext %410)
  %412 = call zeroext i8 @xtime(i8 zeroext %411)
  %413 = zext i8 %412 to i32
  %414 = mul nsw i32 0, %413
  %415 = xor i32 %409, %414
  %416 = load i8, i8* %2, align 1
  %417 = call zeroext i8 @xtime(i8 zeroext %416)
  %418 = call zeroext i8 @xtime(i8 zeroext %417)
  %419 = call zeroext i8 @xtime(i8 zeroext %418)
  %420 = zext i8 %419 to i32
  %421 = mul nsw i32 1, %420
  %422 = xor i32 %415, %421
  %423 = load i8, i8* %2, align 1
  %424 = call zeroext i8 @xtime(i8 zeroext %423)
  %425 = call zeroext i8 @xtime(i8 zeroext %424)
  %426 = call zeroext i8 @xtime(i8 zeroext %425)
  %427 = call zeroext i8 @xtime(i8 zeroext %426)
  %428 = zext i8 %427 to i32
  %429 = mul nsw i32 0, %428
  %430 = xor i32 %422, %429
  %431 = load i8, i8* %3, align 1
  %432 = zext i8 %431 to i32
  %433 = mul nsw i32 1, %432
  %434 = load i8, i8* %3, align 1
  %435 = call zeroext i8 @xtime(i8 zeroext %434)
  %436 = zext i8 %435 to i32
  %437 = mul nsw i32 0, %436
  %438 = xor i32 %433, %437
  %439 = load i8, i8* %3, align 1
  %440 = call zeroext i8 @xtime(i8 zeroext %439)
  %441 = call zeroext i8 @xtime(i8 zeroext %440)
  %442 = zext i8 %441 to i32
  %443 = mul nsw i32 1, %442
  %444 = xor i32 %438, %443
  %445 = load i8, i8* %3, align 1
  %446 = call zeroext i8 @xtime(i8 zeroext %445)
  %447 = call zeroext i8 @xtime(i8 zeroext %446)
  %448 = call zeroext i8 @xtime(i8 zeroext %447)
  %449 = zext i8 %448 to i32
  %450 = mul nsw i32 1, %449
  %451 = xor i32 %444, %450
  %452 = load i8, i8* %3, align 1
  %453 = call zeroext i8 @xtime(i8 zeroext %452)
  %454 = call zeroext i8 @xtime(i8 zeroext %453)
  %455 = call zeroext i8 @xtime(i8 zeroext %454)
  %456 = call zeroext i8 @xtime(i8 zeroext %455)
  %457 = zext i8 %456 to i32
  %458 = mul nsw i32 0, %457
  %459 = xor i32 %451, %458
  %460 = xor i32 %430, %459
  %461 = load i8, i8* %4, align 1
  %462 = zext i8 %461 to i32
  %463 = mul nsw i32 1, %462
  %464 = load i8, i8* %4, align 1
  %465 = call zeroext i8 @xtime(i8 zeroext %464)
  %466 = zext i8 %465 to i32
  %467 = mul nsw i32 0, %466
  %468 = xor i32 %463, %467
  %469 = load i8, i8* %4, align 1
  %470 = call zeroext i8 @xtime(i8 zeroext %469)
  %471 = call zeroext i8 @xtime(i8 zeroext %470)
  %472 = zext i8 %471 to i32
  %473 = mul nsw i32 0, %472
  %474 = xor i32 %468, %473
  %475 = load i8, i8* %4, align 1
  %476 = call zeroext i8 @xtime(i8 zeroext %475)
  %477 = call zeroext i8 @xtime(i8 zeroext %476)
  %478 = call zeroext i8 @xtime(i8 zeroext %477)
  %479 = zext i8 %478 to i32
  %480 = mul nsw i32 1, %479
  %481 = xor i32 %474, %480
  %482 = load i8, i8* %4, align 1
  %483 = call zeroext i8 @xtime(i8 zeroext %482)
  %484 = call zeroext i8 @xtime(i8 zeroext %483)
  %485 = call zeroext i8 @xtime(i8 zeroext %484)
  %486 = call zeroext i8 @xtime(i8 zeroext %485)
  %487 = zext i8 %486 to i32
  %488 = mul nsw i32 0, %487
  %489 = xor i32 %481, %488
  %490 = xor i32 %460, %489
  %491 = load i8, i8* %5, align 1
  %492 = zext i8 %491 to i32
  %493 = mul nsw i32 0, %492
  %494 = load i8, i8* %5, align 1
  %495 = call zeroext i8 @xtime(i8 zeroext %494)
  %496 = zext i8 %495 to i32
  %497 = mul nsw i32 1, %496
  %498 = xor i32 %493, %497
  %499 = load i8, i8* %5, align 1
  %500 = call zeroext i8 @xtime(i8 zeroext %499)
  %501 = call zeroext i8 @xtime(i8 zeroext %500)
  %502 = zext i8 %501 to i32
  %503 = mul nsw i32 1, %502
  %504 = xor i32 %498, %503
  %505 = load i8, i8* %5, align 1
  %506 = call zeroext i8 @xtime(i8 zeroext %505)
  %507 = call zeroext i8 @xtime(i8 zeroext %506)
  %508 = call zeroext i8 @xtime(i8 zeroext %507)
  %509 = zext i8 %508 to i32
  %510 = mul nsw i32 1, %509
  %511 = xor i32 %504, %510
  %512 = load i8, i8* %5, align 1
  %513 = call zeroext i8 @xtime(i8 zeroext %512)
  %514 = call zeroext i8 @xtime(i8 zeroext %513)
  %515 = call zeroext i8 @xtime(i8 zeroext %514)
  %516 = call zeroext i8 @xtime(i8 zeroext %515)
  %517 = zext i8 %516 to i32
  %518 = mul nsw i32 0, %517
  %519 = xor i32 %511, %518
  %520 = xor i32 %490, %519
  %521 = trunc i32 %520 to i8
  %522 = load [4 x [4 x i8]]*, [4 x [4 x i8]]** @state, align 4
  %523 = load i32, i32* %1, align 4
  %524 = getelementptr inbounds [4 x [4 x i8]], [4 x [4 x i8]]* %522, i32 0, i32 %523
  %525 = getelementptr inbounds [4 x i8], [4 x i8]* %524, i32 0, i32 3
  store i8 %521, i8* %525, align 1
  br label %526

; <label>:526:                                    ; preds = %9
  %527 = load i32, i32* %1, align 4
  %528 = add nsw i32 %527, 1
  store i32 %528, i32* %1, align 4
  br label %6

; <label>:529:                                    ; preds = %6
  ret void
}

; Function Attrs: noinline nounwind optnone
define internal zeroext i8 @getSBoxInvert(i8 zeroext) #0 {
  %2 = alloca i8, align 1
  store i8 %0, i8* %2, align 1
  %3 = load i8, i8* %2, align 1
  %4 = zext i8 %3 to i32
  %5 = getelementptr inbounds [256 x i8], [256 x i8]* @rsbox, i32 0, i32 %4
  %6 = load i8, i8* %5, align 1
  ret i8 %6
}

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="arm926ej-s" "target-features"="+armv5tej,+dsp,+strict-align,-crc,-dotprod,-hwdiv,-hwdiv-arm,-ras,-thumb-mode" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"min_enum_size", i32 4}
!2 = !{!"clang version 7.0.1 (tags/RELEASE_701/final)"}
