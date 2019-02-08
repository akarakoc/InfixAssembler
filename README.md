# InfixAssembler
Converts infix expression to postfix expression and creates a86 code 

Introduction
The aim of this project is designing a program which creates A86 code output in order to calculate result of an infix operation by using Stack.

Technique
This program takes an in-fix expression and as a result of the process, creates post-fix output and its corresponding assembly code. The input may contain alphanumeric constants, parenthesis “(,[,{“ and operators “+,-,*,/”. If an infix expression contains these type of characters and correct logical order, the code generates post-fix and its A86 code by using stack operations.

Basically the required operations are defined via functions. When program is executed, the given input expression is read by the program character by character. If alphanumeric character matches, it is directly appended to the post-fix expression. If an operator matches, according to the precedence of the operator with respect to operator which resides at the top of the stack, whichr is called from the stack in order to append post-fix expression and existing operator is pushed to the stack for the next iteration of the loop. If an open parenthesis matches, it is directly pushed to the stack for the evaluation of the next instruction. If closed parenthesis exists, all stack values are popped in order to append to the post-fix string expression.


![alt text](https://github.com/akarakoc/InfixAssembler/blob/master/IMG/outline.png)

Figure 1: Logical Diagram of the code generator program.



Results
As an example of infix expression, the program creates the following responses:

![alt text](https://github.com/akarakoc/InfixAssembler/blob/master/IMG/sample.png)

Figure 2: Execution of the program

![alt text](https://github.com/akarakoc/InfixAssembler/blob/master/IMG/sample2.png)

Figure 3: Corresponding A86 code

![alt text](https://github.com/akarakoc/InfixAssembler/blob/master/IMG/sample3.png)

Figure 4: Result of the A86 code.
