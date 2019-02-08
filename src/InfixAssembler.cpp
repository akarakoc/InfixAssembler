//============================================================================
// Name        : InfixAssembler
// Author      : Ali Karakoç
// Version     : 1.0
//============================================================================

#include<iostream>
#include<stack>
#include<string>
#include<cstdlib>
#include<fstream>

using namespace std;

// Assigns weight to the operators according to their precedence
int WeightOP(char a)
{
	int weight = -1;
	switch(a)
	{
	case '+':
	case '-':
		weight = 1;
		break ;
	case '*':
	case '/':
		weight = 2;
		break ;
	}
	return weight;
}
// Determines the precedence and returns true or false
int Precedence(char x1, char x2)

{
	int WeightOP1 = WeightOP(x1);
	int WeightOP2 = WeightOP(x2);
	if(WeightOP1 == WeightOP2)
	{
		return true;
	}
	return WeightOP1 > WeightOP2 ?  true: false;
}
// Converts decimal to hexadecimal
template <typename I> std::string IntToStr(I w, size_t hex_len = sizeof(I)<<1) {
    static const char* digits = "0123456789ABCDEF";
    std::string rc(hex_len,'0');
    for (size_t i=0, j=(hex_len-1)*4 ; i<hex_len; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    rc +="h";
    return rc;
}
// Gives postfix output of the formula
string FPostfix(string formula)
{
	stack<char> S; //We will use stack in order to evaluate postfix operations
	string postfix = "";
	//Reads each character/number from left to the right-end
	for(int i = 0;i< formula.length();i++) {
		//Checks whether the selected character is operand or not, if it is operand, it appends to the postfix string
		if((formula[i] == ' ') || (formula[i] >= '0' && formula[i] <= '9') || (formula[i] >= 'a' && formula[i]<= 'z') || (formula[i] >= 'A' && formula[i] <= 'Z'))
		{
			postfix +=formula[i];
		}

		//Push the operator to the stack according to Precedence, if current precedence is lower
		//than the top ıf the stack pop and append the values to postfix string
		else if(formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/')
		{
			postfix +=" ";
			while(!S.empty() && !(S.top() == '(' || S.top() == '{' || S.top()=='[') && Precedence(S.top(),formula[i]))
			{
				postfix+= S.top();
				S.pop();
			}
			S.push(formula[i]);
		}

		//Push the parantesis to the stack
		else if(formula[i] == '(' || formula[i] == '{' || formula[i] == '[')
		{
			S.push(formula[i]);
		}

        //If closing paranthesis matches, pop and append the stack values while matching opening paranthesis
		else if(formula[i] == ')' || formula[i] == '}' || formula[i] ==']')
		{
			while(!S.empty() && !(S.top() == '(' || S.top() == '{' || S.top()=='[')) {
				postfix += S.top();
				S.pop();
			}
			S.pop();
		}
	}
    //Append remaining elements to the postfix
	while(!S.empty()) {
		postfix += S.top();
		S.pop();
	}

	return postfix;
}

string FAssembly(string formula)
{

	string assm = ""; // Initialize postfix as empty string.
	ofstream fn1;
	fn1.open("code.asm");
	fn1 <<"\n\n";
	fn1 <<"code segment\n"<<endl;

	for(int i = 0;i< formula.length();i++) {
		// Scanning each character from left.
		// If the value is operator then insert related assembly operation(for the both space and operands neighborhood)
		if((formula[i] == ' ' || (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/')) && (formula[i-1] == ' ' || ((formula[i-1] == '+' || formula[i-1] == '-' || formula[i-1] == '*' || formula[i-1] == '/')))){
			fn1<<"\t\t\tPOP BX ;Pop the value from Stack and Insert to BX."<<endl;
			fn1<<"\t\t\tPOP AX ;Pop the value from Stack and Insert to AX."<<endl;
			if(formula[i] == '+'){
				fn1<<"\t\t\tADD AX,BX ;Add AX and BX."<<endl;
				fn1<<"\t\t\tPUSH AX ;Push the result to Stack."<<endl;
			}else if(formula[i] == '-'){
				fn1<<"\t\t\tSUB AX,BX ;Substract AX and BX"<<endl;
				fn1<<"\t\t\tPUSH AX ;Push the result to Stack."<<endl;
			}else if(formula[i] == '*'){
				fn1<<"\t\t\tMUL BX ;Multiplicate AX and BX."<<endl;
				fn1<<"\t\t\tXOR DX,DX ;Prevent overflow reset DX (DX:AX)."<<endl;
				fn1<<"\t\t\tPUSH AX ;Push the result to Stack."<<endl;
			}else if(formula[i] == '/'){
				fn1<<"\t\t\tXOR DX,DX ;Prevent overflow reset DX (DX:AX)."<<endl;
				fn1<<"\t\t\tDIV BX ;Divide AX to BX."<<endl;
				fn1<<"\t\t\tPUSH AX ;Push the result to Stack."<<endl;
			}
			continue;
		}
		//If the value is operator or space, gather all collected numbers in order to convert from string to decimal.
		if(formula[i] == ' ' || (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/')){
			int assn;
			assn = atoi(assm.c_str());
			assm = IntToStr(assn);
			fn1<<"\t\t\tPUSH "<<assm<<" ;Push the value to Stack"<<endl;
			assm = "";
		}else{
			assm +=formula[i];
		}
		// Append convenient assembly commands with respect to operand
		if((formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/')){
			fn1<<"\t\t\tPOP BX ;Pop the value from Stack and Insert to BX."<<endl;
			fn1<<"\t\t\tPOP AX ;Pop the value from Stack and Insert to AX."<<endl;
			if(formula[i] == '+'){
				fn1<<"\t\t\tADD AX,BX ;Add AX and BX."<<endl;
				fn1<<"\t\t\tPUSH AX ;Push the result to Stack."<<endl;
			}else if(formula[i] == '-'){
				fn1<<"\t\t\tSUB AX,BX ;Substract AX and BX"<<endl;
				fn1<<"\t\t\tPUSH AX ;Push the result to Stack."<<endl;
			}else if(formula[i] == '*'){
				fn1<<"\t\t\tMUL BX ;Multiplicate AX and BX."<<endl;
				fn1<<"\t\t\tXOR DX,DX ;Prevent overflow reset DX (DX:AX)."<<endl;
				fn1<<"\t\t\tPUSH AX ;Push the result to Stack."<<endl;
			}else if(formula[i] == '/'){
				fn1<<"\t\t\tXOR DX,DX ;Prevent overflow reset DX (DX:AX)."<<endl;
				fn1<<"\t\t\tDIV BX ;Divide AX to BX."<<endl;
				fn1<<"\t\t\tPUSH AX ;Push the result to Stack."<<endl;
			}
		}

	}
	//This output writes results to the screen in hexadecimal format
	fn1<<"\t\t\tPOP AX ;Pop the operation result to AX register.\n\t\t\tCALL PrtHex ;Call the print function.\n\t\t\tMOV  AX,4C00h ;Assign the service number for interrupt (AH=4ch and AL=00h).\n\t\t\tINT  21h ;Execute the instruction with OS interrupt.\n\nPrtHex      PROC NEAR USES AX BX CX ;Print sub-routine.\n\n\t\t\tMOV  BX,OFFSET Hex ;Hexadecimal character set.\n\t\t\tMOV  CX,04h ;Assign lenght of the string.\nHexLoop:    PUSH  AX ;Push result of the postfix operation.\n\t\t\tMOV  AL,AH ;Transfer the value to AL register.\n\t\t\tSHR  AL,04h ;Right shift the value.\n\t\t\tXLATB ;Reads the byte at the index in the translation table, and stores this value in AL.\n\t\t\tMOV  DL,AL ;Character to write on AL.\n\t\t\tMOV  AH,02 ;Writes on the screen.\n\t\t\tINT  21h ;Execute the instruction with OS interrupt.\n\t\t\tPOP  AX ;Pop the value from stack.\n\t\t\tSHL  AX,04h ;Left shift the value.\n\t\t\tLOOP HexLoop ;Loop\n\t\t\tMOV  AH,02 ;Writes on the screen.\n\t\t\tMOV  DL,'h' ;Put the character 'h' at the end of the string.\n\t\t\tINT  21h ;Execute the instruction with OS interrupt.\n\t\t\tRET ;Return main Proc.\nPrtHex      ENDP ;OS interruption of finish operation.\n\nHex         db  '0123456789ABCDEF' ;Hexadecimal Character Set.\n\n.end ;End of the program.\n";
	fn1.close();
	return "";
}
//main fuction
int main()
{
	string formula;
	cout<<"Enter Infix formula"<<endl;
	getline(cin,formula);
	string postfix = FPostfix(formula);
	cout<<"Output = "<<postfix<<endl;
	string assm = FAssembly(postfix);
}

