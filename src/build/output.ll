; ModuleID = 'program'
source_filename = "program"

%A_vtable = type { ptr }
%A = type { i32, ptr, double, double }

@current_stack_depth = private global i32 0
@A_vtable_instance = global %A_vtable { ptr @_A_getX }

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

define i32 @main() {
entry:
  %x = alloca double, align 8
  %y = alloca double, align 8
  ret i32 0
}

define double @_A_getX(ptr %0) {
entry:
  %tmp = load %A, ptr %0, align 8
  %field_ptr = getelementptr inbounds %A, %A %tmp, i32 0, i32 2
  ret void
}
