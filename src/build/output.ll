; ModuleID = 'program'
source_filename = "program"

@current_stack_depth = private global i32 0
@error_msg = private unnamed_addr constant [79 x i8] c"\1B[31m!!RUNTIME ERROR: Stack overflow detected in function 'tan'. Line: 4.\0A\1B[0m\00", align 1

declare void @strcpy(ptr, ptr)

declare void @strcat(ptr, ptr)

declare i64 @strlen(ptr)

declare double @sqrt(double)

declare double @sin(double)

declare double @cos(double)

declare double @log(double)

declare double @exp(double)

declare i32 @rand()

declare double @pow(double, double)

declare double @fmod(double, double)

declare ptr @malloc(i64)

declare i32 @printf(ptr, ...)

declare i32 @puts(ptr)

declare i32 @snprintf(ptr, i64, ptr, ...)

declare i32 @strcmp(ptr, ptr)

declare void @exit(i32)

define double @tan() {
entry:
  %load_depth = load i32, ptr @current_stack_depth, align 4
  %inc_depth = add i32 %load_depth, 1
  store i32 %inc_depth, ptr @current_stack_depth, align 4
  %cmp_overflow = icmp sgt i32 %inc_depth, 0
  br i1 %cmp_overflow, label %stack_overflow, label %func_body

function_exit:                                    ; preds = %func_body
  %load_depth_final = load i32, ptr @current_stack_depth, align 4
  %dec_depth = sub i32 %load_depth_final, 1
  store i32 %dec_depth, ptr @current_stack_depth, align 4
  ret double 1.200000e+01

stack_overflow:                                   ; preds = %entry
  %0 = call i32 @puts(ptr @error_msg)
  call void @exit(i32 0)
  unreachable

func_body:                                        ; preds = %entry
  br label %function_exit
}

define i32 @main() {
entry:
  ret i32 0
}
