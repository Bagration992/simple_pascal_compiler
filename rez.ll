; ModuleID = 'Moj modul'

@0 = private unnamed_addr constant [4 x i8] c"%f\0A\00"

declare i32 @printf(i8*, ...)

define i32 @main() {
entry:
  %d = alloca double
  %c = alloca double
  %b = alloca double
  %a = alloca double
  store double 1.000000e+00, double* %a
  store double 2.000000e+00, double* %b
  store double 3.000000e+00, double* %c
  store double 4.000000e+00, double* %d
  br i1 true, label %then, label %else

then:                                             ; preds = %entry
  %printfCall = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double 1.000000e+00)
  br label %ifcont

else:                                             ; preds = %entry
  %printfCall1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double 2.000000e+00)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  br i1 false, label %then2, label %else5

then2:                                            ; preds = %ifcont
  %printfCall3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double 1.000000e+00)
  %printfCall4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double 3.000000e+00)
  br label %ifcont8

else5:                                            ; preds = %ifcont
  %printfCall6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double 2.000000e+00)
  %printfCall7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double 4.000000e+00)
  br label %ifcont8

ifcont8:                                          ; preds = %else5, %then2
  %0 = load double, double* %b
  %printfCall9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double %0)
  br i1 false, label %then10, label %else11

then10:                                           ; preds = %ifcont8
  %1 = load double, double* %b
  %tmpadd = fadd double %1, 1.000000e+00
  store double %tmpadd, double* %b
  br label %ifcont12

else11:                                           ; preds = %ifcont8
  %2 = load double, double* %b
  %tmpsub = fsub double %2, 1.000000e+00
  store double %tmpsub, double* %b
  br label %ifcont12

ifcont12:                                         ; preds = %else11, %then10
  %3 = load double, double* %b
  %printfCall13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double %3)
  br i1 true, label %then14, label %ifcont18

then14:                                           ; preds = %ifcont12
  br i1 true, label %then15, label %ifcont17

then15:                                           ; preds = %then14
  %printfCall16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), double 1.000000e+01)
  br label %ifcont17

ifcont17:                                         ; preds = %then15, %then14
  br label %ifcont18

ifcont18:                                         ; preds = %ifcont17, %ifcont12
  ret i32 0
}
