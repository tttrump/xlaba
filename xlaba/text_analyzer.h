#pragma once
#include <string>
#include <vector>

using namespace std;

enum class lexemeType
{
	Id,
	IntNumber,
	FloatNumber,
	Int,
	Float,
	ArrayInt,
	ArrayFloat,
	If,
	Else,
	While,
	Read,
	Write,
	LeftBrace,
	RightBrace,
	LeftSquareBracket,
	RightSquareBracket,
	LeftRoundBracket,
	RightRoundBracket,
	Plus,
	Minus,
	Multiply,
	Divide,
	Semicolon,
	Comma,
	Less,
	Assign,
	More,
	Equal,
	LessOrEqual,
	MoreOrEqual,
	NotEqual,
	Finish,
	Error
};

struct lexeme
{
	lexemeType lexeme_type;
	string value;
	int line;
	int pos;
};

class text_analyzer {
public:
	void run();
	vector<lexeme> get_data();
	text_analyzer(const string&);

private:
	lexeme next_lexeme();
	bool ischar(char ch);

	string program_text;
	int current_index;
	vector<lexeme> data;
};

//text(char *) -> lex_anal(text) -> lexemes(lexeme *) -> synt_anal(lexemes) -> OPS -> interpret(OPS)