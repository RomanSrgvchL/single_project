#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main()
{
	setlocale(0, "");

	vector<string> tokens =
	{
	"(", ")", "[", "]", "{", "}",
	"int", "double", "char", "string",
	"\"", "\'", ".", ",", "//", ";", 
	"=", "+", "-", "*", "/", "%",  ">", "<",  "|", "&", "!",
	"<<", ">>", "||", "&&","++", "--", ">=", "<=", "==", "!=", "/=", "+=", "-=", "%=", "*=",
	};
	//16 - 26, 27 - 41

	bool utification = false;
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
	int count = 0, flag = 1;
	for (int i = 0; i < code.size(); i++)
	{
		if ((code[i] != '\"') && (count % 2 == 0))
			copycode.push_back(code[i]);
		else if ((code[i] == '\"') && !((i != 0) && (code[i - 1] == '\\')))
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
			code.push_back(copycode[i]);
		else if ((copycode[i] == '\'') && !((i != 0) && (copycode[i - 1] == '\\')))
		{
			code.push_back(copycode[i]);
			count += 1;
		}
	}
	copycode.clear();
	for (int i = 1; i < code.size(); i++)
	{
		if (!((code[i - 1] == '/') && (code[i] == '/')) && (flag != 0))
			copycode.push_back(code[i - 1]);
		else if ((code[i - 1] == '/') && (code[i] == '/'))
			flag = 0;
		else if (code[i] == '\n')
			flag = 1;
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
					if ((n > 15) && (n < 27) && (i + 1 < code.size()))
					{
						string x = string(1, code[i]) + string(1, code[i + 1]);
						for (int t = 27; t < 42; t++)
						{
							if (x == tokens[t])
							{
								lexemes.push_back(x);
								lexeme = "";
								i++;
								n = tokens.size();
								utification = true;
								break;
							}
						}
						if (!utification)
						{
							lexemes.push_back(tokens[n]);
							lexeme = "";
							break;
						}
						else utification = false;
					}
					else 
					{
						lexemes.push_back(tokens[n]);
						lexeme = "";
						break;
					}
					
				}
				else if (lexeme.find(tokens[n]) != std::string::npos)
				{ 
					if ((n > 15) && (n < 27) && (i + 1 < code.size()))
					{
						string x = string(1, code[i]) + string(1, code[i + 1]);
						for (int t = 27; t < 42; t++)
						{
							if (x == tokens[t])
							{
								lexeme.pop_back();
								lexemes.push_back(lexeme);
								lexemes.push_back(x);
								lexeme = "";
								i++;
								n = tokens.size();
								utification = true;
								break;
							}
						}
						if (!utification)
						{
							lexeme.pop_back();
							lexemes.push_back(lexeme);
							lexemes.push_back(tokens[n]);
							lexeme = "";
							break;
						}
						else utification = false;
					}
					else
					{
						lexeme.pop_back();
						lexemes.push_back(lexeme);
						lexemes.push_back(tokens[n]);
						lexeme = "";
						break;
					}

				}
			}
		}
		else
		{
			if ((lexeme != ""))
				lexemes.push_back(lexeme);
			if (code[i] == '\n')
				lexemes.push_back("\n");	
			lexeme = "";
		}
	}
	
	cout << "-------------\n";
	for (int i = 0; i < lexemes.size(); i++)
		if (lexemes[i] != "\n")
			cout << lexemes[i] << " ";
		else cout << endl;
	return 0;
}