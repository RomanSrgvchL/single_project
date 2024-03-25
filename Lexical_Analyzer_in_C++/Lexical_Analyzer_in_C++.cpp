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
	"\"", "\'", ".", ",", ";",
	"=", "+", "-", "*", "/", "%",  ">", "<",  "|", "&", "!",
	"<<", ">>", "||", "&&","++", "--", ">=", "<=", "==", "!=", "/=", "+=", "-=", "%=", "*=",
	"int", "double", "char", "string"
	};
	// 0 - 5, 6 - 10, 11 - 21, 22 - 36, 37 - 40
	// a[0-1], a[2-3], a[4-5], a[6-7], a[8-9]
	vector<char> valid_characters =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e',
		'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J', 'j',
		'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o',
		'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's', 'T', 't',
		'U', 'u', 'V', 'v', 'W', 'w', 'x', 'x', 'Y', 'y',
		'Z', 'z', '_'
	};
	// 0 - 9, 10 - 61, 62
	// a[10-11], a[12-13], a[14]
	vector<string> keywords =
	{
	"asm", "double", "new", "switch",
	"auto", "else", "operator", "template",
	"break", "enum", "private", "this",
	"case",	"extern", "protected", "throw",
	"catch", "float", "publin",	"try"
	"char",	"for", "register", "typedef"
	"class", "friend", "return", "union",
	"const", "goto",	"short", "unsigned",
	"continue",	"if", "signed",	"virtual",
	"default", "inline", "sizeof", "void",
	"delete", "int", "static", "volatile",
	"do", "long", "struct",	"while"
	};

	int a[15] = { 0, 5, 6, 10, 11, 21, 22, 36, 37, 40, 0, 9, 10, 61, 62 };

	bool utification = false;
	vector<string> lexemes, space;
	vector<char> code, copycode;
	string lexeme, str, end = "end";

	cout << "Введите ваш код (для завершения введите end):\n\n";

	// записал код посимвольно в code
	while (str != end)
	{
		getline(cin, str);
		if (str == end) break;
		for (int i = 0; i < str.length(); i++)
			code.push_back(str[i]);
		code.push_back('\n');
	}
	if (code.size() > 1) code.pop_back();

	if (code.size() == 0)
	{
		cout << "Вы ничего не ввели";
		return 0;
	}

#pragma region Delete
	int count = 0, flag = 1;
	for (int i = 0; i < code.size(); i++)
	{
		if ((code[i] != '\"') && (count % 2 == 0))
			copycode.push_back(code[i]);
		else if ((code[i] == '\"') && !((i > 1) && (code[i - 1] == '\\') && (code[i - 2] != '\\')))
		{
			copycode.push_back(code[i]);
			count += 1;
		}
		else if ((code[i] == '\"') && (i > 1) && (code[i - 1] == '\\') && (code[i - 2] != '\\'))
			copycode.push_back(code[i]);
	}
	count = 0;
	code.clear();
	for (int i = 0; i < copycode.size(); i++)
	{
		if ((copycode[i] != '\'') && (count % 2 == 0))
			code.push_back(copycode[i]);
		else if ((copycode[i] == '\'') && !((i > 1) && (copycode[i - 1] == '\\') && (copycode[i - 2] != '\\')))
		{
			code.push_back(copycode[i]);
			count += 1;
		}
		else if ((copycode[i] == '\'') && (i > 1) && (copycode[i - 1] == '\\') && (copycode[i - 2] != '\\'))
			code.push_back(copycode[i]);
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
	copycode.clear();
#pragma endregion

	// нахожу лексемы
	for (int i = 0; i < code.size(); i++)
	{
		if ((code[i] != ' ') && (code[i] != '\n'))
		{
			lexeme += code[i];
			for (int n = 0; n < tokens.size(); n++)
			{
				if ((lexeme == tokens[n]) && !(((lexeme == "int") || (lexeme == "double") || (lexeme == "char") ||
					(lexeme == "string")) && (i + 1 < code.size()) && (code[i + 1] != ' ')))
				{
					if ((n >= a[4]) && (n <= a[5]) && (i + 1 < code.size()))
					{
						string x = string(1, code[i]) + string(1, code[i + 1]);
						for (int t = a[6]; t <= a[7]; t++)
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
				else if ((lexeme.find(tokens[n]) != std::string::npos) && !(((lexemes.size() != 0) && ((lexemes.back() == "int") || (lexemes.back() == "double") ||
					(lexemes.back() == "char") || (lexemes.back() == "string"))) &&
					!((code[i] == '(') || (code[i] == '[') || (code[i] == '{') || (code[i] == ';') || (code[i] == ','))) && !((n >= 37) && (n <= 40)))
				{
					if ((n >= a[4]) && (n <= a[5]) && (i + 1 < code.size()))
					{
						string x = string(1, code[i]) + string(1, code[i + 1]);
						for (int t = a[6]; t <= a[7]; t++)
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
				else if ((i + 1 == code.size()) && (n + 1 == tokens.size()))
				{
					lexemes.push_back(lexeme);
					break;
				}
			}
		}
		else
		{
			if (lexeme != "") lexemes.push_back(lexeme);
			if (code[i] == '\n') lexemes.push_back("\n");
			lexeme = "";
		}
	}

	cout << "-----------------------------------------------------------\n";

	int lines = 1;
	cout << lines << ") ";
	for (int i = 0; i < lexemes.size(); i++)
		if (lexemes[i] != "\n")
			cout << lexemes[i] << " ";
		else cout << endl << ++lines << ") ";

	int brackets[6] = { 0, 0, 0, 0, 0, 0 };
	// ()[]{};
	for (int i = 0; i < lexemes.size(); i++)
	{
		for (int n = 0; n < 6; n++)
		{
			if (lexemes[i] == tokens[n])
				brackets[n]++;
		}
	}

	cout << "\n-----------------------------------------------------------\n\n";

	//проверяю соответствие открывающихся и закрывающихся скобок
	if (brackets[0] != brackets[1])
		cout << "Кол-во открывающихся круглых скобок не соответствует закрывающимся: " << brackets[0] << " '(' и " << brackets[1] << " ')'" << endl;
	if (brackets[2] != brackets[3])
		cout << "Кол-во открывающихся квадратных скобок не соответствует закрывающимся: " << brackets[2] << " '[' и " << brackets[3] << " ']'" << endl;
	if (brackets[4] != brackets[5])
		cout << "Кол-во открывающихся фигурных скобок не соответствует закрывающимся: " << brackets[4] << " '{' и " << brackets[5] << " '}'" << endl;

	// удаляю всё после #include
	vector<string> copylexemes;
	for (int i = 0; i < lexemes.size(); i++)
	{
		copylexemes.push_back(lexemes[i]);
		if (lexemes[i] == "#include")
		{
			for (i + 1; i < lexemes.size(); i++)
			{
				if (lexemes[i] == "\n")
				{
					copylexemes.push_back(lexemes[i]);
					break;
				}
			}
		}
	}
	lexemes.clear();
	for (int i = 0; i < copylexemes.size(); i++)
		lexemes.push_back(copylexemes[i]);


	// проверяю допустимое ли имя идентификатора
	lines = 1;
	bool special = false;
	for (int i = 0; i < lexemes.size(); i++)
	{
		if (lexemes[i] == "\n")
		{
			lines++;
			continue;
		}
		for (int n = a[8]; n <= a[9]; n++)
		{
			if ((i + 1 < lexemes.size()) && ((lexemes[i] == tokens[n]) && (lexemes[i + 1] != "*") && (lexemes[i + 1] != ">") || special))
			{
				if (special) special = !special;
				string x = lexemes[i + 1];
				if ((x[0] == '0') || (x[0] == '1') || (x[0] == '2') || (x[0] == '3') || (x[0] == '4') ||
					(x[0] == '5') || (x[0] == '6') || (x[0] == '7') || (x[0] == '8') || (x[0] == '9'))
				{
					cout << "Идентификатор не должен начинаться с цифры, строка " << lines << endl;
					break;
				}
				if (x == "\n")
				{
					cout << "Отсутствует идентификатор, строка " << lines << endl;
					break;
				}
				if (find(keywords.begin(), keywords.end(), x) != keywords.end())
				{
					cout << "Идентификатор не должен совпадать с ключевыми словами, строка " << lines << endl;
					break;
				}
				for (int m = 0; m < x.length(); m++)
				{
					if (find(valid_characters.begin(), valid_characters.end(), x[m]) == valid_characters.end())
					{
						cout << "Недопустимые символы в идентификаторе, строка " << lines << endl;
						m = x.length();
						break;
					}
				}
				i++;
			}
			else if ((lexemes[i] == tokens[n]) && (i + 1 < lexemes.size()) && ((lexemes[i + 1] == "*") || (lexemes[i + 1] == ">")))
			{
				special = true;
				break;
			}

			else if ((lexemes[i] == tokens[n]) && (i + 1 == lexemes.size()))
			{
				cout << "Отсутствует идентификатор, строка " << lines << endl;
				break;
			}

		}
	}
	
	// посчитать количество ; в for
	lines = 1;
	count = 0;
	for (int i = 0; i < lexemes.size(); i++)
	{
		count = 0;
		if (lexemes[i] == "\n")
		{
			lines += 1;
			continue;
		}
		if ((lexemes[i] == "for"))
		{
			for (i; (i < lexemes.size()) && (lexemes[i] != "\n"); i++)
				if (lexemes[i] == ";") count += 1;
			if (count > 2)
				cout << "Обнаружены лишние точки с запятой, строка " << lines << endl;
			else if (count == 1)
				cout << "Необходима точка с запятой, строка " << lines << endl;
			else if (count == 0)
				cout << "Необходимо поставить две точки с запятой, строка " << lines << endl;
			lines++;
		}
	}
	
	// стираю всю строку, если в ней есть if for while
	copylexemes.clear();
	for (int i = 0; i < lexemes.size(); i++)
	{
		copylexemes.push_back(lexemes[i]);
		if ((lexemes[i] == "if") || (lexemes[i] == "while") || (lexemes[i] == "for") || (((lexemes[i] == "int") || (lexemes[i] == "double")
			|| (lexemes[i] == "char") || (lexemes[i] == "string")) && (i + 2 < lexemes.size()) && (lexemes[i + 1] + lexemes[i + 2] != "()")) && (i + 1 < lexemes.size()))
		{
			for (i + 1; i < lexemes.size(); i++)
			{
				if (lexemes[i] == "\n")
				{
					copylexemes.push_back(lexemes[i]);
					break;
				}
			}
		}
	}
	lexemes.clear();
	for (int i = 0; i < copylexemes.size(); i++)
		lexemes.push_back(copylexemes[i]);


	// точка с запятой в строке с cout cin endl = /= += -= *= %= ++ -- break return continue ) int double string char
	lines = 1;
	bool semicolon = false;
	for (int i = 0; i < lexemes.size(); i++)
	{
		if ((lexemes[i] == "cout") || (lexemes[i] == "cin") || (lexemes[i] == "endl") || (lexemes[i] == "=") || (lexemes[i] == "+=") ||
			(lexemes[i] == "-=") || (lexemes[i] == "*=") || (lexemes[i] == "/=") || (lexemes[i] == "%n") ||
			(((lexemes[i] == "int") || (lexemes[i] == "double") || (lexemes[i] == "string") || (lexemes[i] == "char")) &&
			(i + 2 < lexemes.size()) && (lexemes[i + 1] + lexemes[i + 2] == "()")) ||
			(lexemes[i] == "++") || (lexemes[i] == "--") || (lexemes[i] == "break") || (lexemes[i] == "return") || (lexemes[i] == "continue") || (lexemes[i] == ")"))
		{
			for (i; i < lexemes.size(); i++)
			{
				if ((lexemes[i] == "\n") || (i + 1 == lexemes.size()))
				{
					cout << "Необходима точка с запятой, строка " << lines << endl;
					lines++;
					break;
				}
				if (lexemes[i] == ";")
				{
					semicolon = true;
					break;
				}
			}
		}
		else if (lexemes[i] == "\n")
		{
			semicolon = false;
			lines++;
		}
	}

	return 0;
}