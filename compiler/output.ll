; ModuleID = 'MyLLVMProgram'
source_filename = "MyLLVMProgram"

@.fmt = private constant [4 x i8] c"%d\0A\00"

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 10, ptr %x, align 4
  %y = alloca i32, align 4
  store i32 5, ptr %y, align 4
  %sum = alloca i32, align 4
  %x1 = load i32, ptr %x, align 4
  %y2 = load i32, ptr %y, align 4
  %addtmp = add i32 %x1, %y2
  store i32 %addtmp, ptr %sum, align 4
  %sum3 = load i32, ptr %sum, align 4
  %0 = call i32 (...) @printf(ptr @.fmt, i32 %sum3)
  ret i32 0
}

declare i32 @printf(...)
