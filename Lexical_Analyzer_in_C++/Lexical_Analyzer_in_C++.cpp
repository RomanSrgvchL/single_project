#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
using namespace std;


void Unification(vector<string>& lexemes, vector<string>& space, string& s1, string& s2)
{
	for (int i = 0; i < lexemes.size(); i++)
	{
		if (lexemes[i] != s1)
			space.push_back(lexemes[i]);
		else if ((i + 1 < lexemes.size()) && (lexemes[i + 1] == s2))
		{
			space.push_back(s1 + s2);
			i++;
		}
		else
			space.push_back(lexemes[i]);
	}
	lexemes.clear();
	for (int i = 0; i < space.size(); i++)
		lexemes.push_back(space[i]);
	space.clear();
}


int main()
{

	setlocale(0, "");

	vector<string> tokens =
	{
	"(", ")", "[", "]", "{", "}",
	"int", "double", "char", "string",
	"=", "+", "-", "*", "/", "%", "++", "--", ">", "<", ">=", "<=", "==", "!=", "/=", "+=", "-=", "%=", "*=", "|", "&", "||", "&&",
	"\"", "\'", ".", ",", "//", ";", "<<", ">>",
	"cout", "cin", "break", "return", "#include", "#define", "if", "for", "else", "while", "do", "vector",
	};
	

	int count = 0, flag = 1;
	vector<string> lexemes, space;
	vector<char> code, copycode;
	string lexeme, str, end = "end";

	cout << "Enter your code (to terminate, enter 'end'.):\n\n";
	
	// записал код посимвольно в code
	while (str != end)
	{
		getline(cin, str);
		if (str == end) break;
		for (int i = 0; i < str.length(); i++)
			code.push_back(str[i]);	
		code.push_back('\n');
	}
	code.pop_back();
	
	#pragma region Delete
	for (int i = 0; i < code.size(); i++)
	{
		if ((code[i] != '\"') && (count % 2 == 0))
		{
			copycode.push_back(code[i]);
		}
		else if (code[i] == '\"')
		{
			copycode.push_back(code[i]);
			count += 1;
		}
	}
	count = 0;
	code.clear();
	for (int i = 0; i < copycode.size(); i++)
	{
		if ((copycode[i] != '\'') && (count % 2 == 0))
		{
			code.push_back(copycode[i]);
		}
		else if (copycode[i] == '\'')
		{
			code.push_back(copycode[i]);
			count += 1;
		}
	}
	copycode.clear();
	for (int i = 1; i < code.size(); i++)
	{
		if (!((code[i - 1] == '/') && (code[i] == '/')) && (flag != 0))
		{
			copycode.push_back(code[i - 1]);
		}
		else if ((code[i - 1] == '/') && (code[i] == '/'))
		{
			flag = 0;
		}
		else if (code[i] == '\n')
		{
			flag = 1;
		}
	};
	if (flag == 1) copycode.push_back(code.back());
	code.clear();
	for (int i = 0; i < copycode.size(); i++)
		code.push_back(copycode[i]);
	#pragma endregion

	// нахожу лексемы
	for (int i = 0; i < code.size(); i++) 
	{
		if ((code[i] != ' ') && (code[i] != '\n'))
		{
			lexeme += code[i];
			for (int n = 0; n < tokens.size(); n++)
			{
				if (lexeme == tokens[n])
				{
					lexemes.push_back(tokens[n]);
					lexeme = "";
					break;
				}
				else if (lexeme.find(tokens[n]) != std::string::npos)
				{ 
					lexeme.pop_back();
					lexemes.push_back(lexeme);
					lexemes.push_back(tokens[n]);
					lexeme = "";
					break;
				}
			}
		}
		else
		{
			if ((lexeme != ""))
				lexemes.push_back(lexeme);
			if (code[i] == '\n')
			{
				lexeme = "\n";
				lexemes.push_back(lexeme);
			}		
			lexeme = "";
		}
	}

	#pragma region Unification
	for (int i = 0; i < lexemes.size(); i++)
		if ((lexemes[i] != "<") && (lexemes[i] != ">") && (lexemes[i] != "+") && (lexemes[i] != "-") && (lexemes[i] != "=") && (lexemes[i] != "%") &&
			(lexemes[i] != "*") && (lexemes[i] != "/") && (lexemes[i] != "!"))
			space.push_back(lexemes[i]);
		else if ((i + 1 < lexemes.size()) && ((lexemes[i] + lexemes[i + 1] == "<<") || (lexemes[i] + lexemes[i + 1] == "<<") || (lexemes[i] + lexemes[i + 1] == ">>") || 
			(lexemes[i] + lexemes[i + 1] == "<<") || (lexemes[i] + lexemes[i + 1] == "==") || (lexemes[i] + lexemes[i + 1] == "++") || (lexemes[i] + lexemes[i + 1] == "--") || 
			(lexemes[i] + lexemes[i + 1] == "+=") || (lexemes[i] + lexemes[i + 1] == "-=") || (lexemes[i] + lexemes[i + 1] == "*=") || (lexemes[i] + lexemes[i + 1] == "/=") || 
			(lexemes[i] + lexemes[i + 1] == "%=") || (lexemes[i] + lexemes[i + 1] == "!=")))
			{
				space.push_back(lexemes[i] + lexemes[i + 1]);
				i++;
			}
		else
			space.push_back(lexemes[i]);

	lexemes.clear();
	for (int i = 0; i < space.size(); i++)
		lexemes.push_back(space[i]);
	space.clear();

	#pragma endregion
	
	cout << "-------------\n";
	for (int i = 0; i < lexemes.size(); i++)
		if (lexemes[i] != "\n")
			cout << lexemes[i] << " ";
		else cout << endl;
	return 0;
}