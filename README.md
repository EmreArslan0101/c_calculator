## C Calculator Project

- My main goal is making a full functioning calculator that written in C with Clang
- It has different syntax error handlers
- It supports decimal, hexadecimal, octal and binary integers and floats
# How to use operators:
  - Summation (+)
    - $$a+b$$
  - Subtraction (-) 
    - $$a-b$$
  - Multiplication (*)
    - $$a*b$$
  - Division (/)
    - $$a/b$$
  - Prime (^)
    - Usage is simple, a^b means $a^b$
  - Radicals (v)
    - Usage is simple, avb means $\sqrt[a]{b}$
# How to use numbers
- Every numbers is divided to two parts:
  - Integer part: They have no dots in their syntax; If they have dots in their syntax number that comes before '.' is integer part
  - Floating Point (Float) part : They have dots in their syntax with or without integer part; They come after the '.'
  - Float numbers syntax : 
    - ".45" is equals to "0.45"; this can be done in decimals 
    - However, in binary, hexadecimal and octal numbers you must use "0n" syntax 
    - n must be x, o or b whichever suits to the case 
    - For example : "0b.1" means "0.5"