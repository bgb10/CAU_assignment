# Simple bison calculator

Simple bison calculator for Class : *CAU-2020-2 Automata And Formal Theory - Midterm Exam Assignment2* <br>

## Notice
- Compiled in bison https://www.gnu.org/software/bison/manual/bison.html and gcc <br>
- Written in Visual Studio Code <br>
- **DO NOT COPY**

## Contents
1. Binary operator : + , - , * , /
2. Unary operator : % , ^
3. Parenthesis : ( , )
4. Last result : _
5. Unary operator sequence : ex. -----------2, ++++++++++2, -+-+-+-+-+2
6. Operator sequence : ex. 2------------3,  2+-+-+-+-+_3
7. Comply operator precedence : ex. 2^3^2 == 512 (^ is right associative), 1+2*3 == 7 (* is prior to +)