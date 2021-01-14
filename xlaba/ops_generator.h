#pragma once
#include <map>
#include <stack>
#include <vector>
#include <string>
#include "text_analyzer.h"

using namespace std;

enum class OpsItemType {
	VariableName,
	IntNumber,
	FloatNumber,
	Operation,
	Error
};

enum class OpsItemOperation {
	Read,
	Write,
	Plus,
	Minus,
	Miltiply,
	Divide,
	Less,
	Assign,
	More,
	Equal,
	LessOrEqual,
	MoreOrEqual,
	NotEqual,
	Jump,
	JumpIfFalse,
	Index,
	Error
};

struct OpsItem {
	OpsItemType type = OpsItemType::Error;
	OpsItemOperation operation = OpsItemOperation::Error;
	string var_name;
	int int_num = 0;
	double float_num = 0;
	int line;
	int pos;

	OpsItem(string name, const lexeme& l)
	{
		type = OpsItemType::VariableName;
		var_name = name;
		line = l.line;
		pos = l.pos;
	}

	OpsItem(OpsItemOperation op, const lexeme& l)
	{
		type = OpsItemType::Operation;
		operation = op;
		line = l.line;
		pos = l.pos;
	}

	OpsItem(int number, const lexeme& l)
	{
		type = OpsItemType::IntNumber;
		int_num = number;
		line = l.line;
		pos = l.pos;
	}

	OpsItem(double number, const lexeme& l)
	{
		type = OpsItemType::FloatNumber;
		float_num = number;
		line = l.line;
		pos = l.pos;
	}

	OpsItem(int number, int l, int p)
	{
		type = OpsItemType::IntNumber;
		int_num = number;
		line = l;
		pos = p;
	}

	OpsItem(double number, int l, int p)
	{
		type = OpsItemType::FloatNumber;
		float_num = number;
		line = l;
		pos = p;
	}
};

struct InterpretData
{
	vector<OpsItem> ops;
	map<string, int> int_table;
	map<string, double> float_table;
	map<string, vector<int>> arrayInt_table;
	map<string, vector<double>> arrayFloat_table;
};

class ops_generator {
public:
	void run();
	InterpretData get_data();
	ops_generator(vector<lexeme>);

private:
	void run_rule();
	void run_task();

	enum class table {
		Int,
		Float,
		ArrayInt,
		ArrayFloat,
	};

	enum class State {
		S, // → intIS | floatIS | arrayIntPS | arrayFloatPS | aH = E; Q | read(aH); Q | write(E); Q | if (C) { SQ }KZQ | while (C) { SQ }Q
		Q, // → aH = E; Q | read(aH); Q | write(E); Q | if (C) { SQ }KZQ | while (C) { SQ }Q | λ
		A, // → aH = E; | read(aH); | write(E); | if (C) { SQ }KZ | while (C) { SQ }
		I, // → aM
		M, // → ,aM | ;
		P, // → a[i]N
		N, // → ,a[i]N | ;
		H, // → [E] | λ
		C, // → (E)VUL | aHVUL | iVUL | fVUL
		L, // → <EZ | >EZ | == EZ | ≤EZ | ≥EZ | !=EZ
		K, // → else { SQ } | λ
		E, // → (E)VU | aHVU | iVU | fVU
		U, // → + TU | -TU | λ
		T, // → (E)V | aHV | iV | fV
		V, // → *FV | /FV | λ
		F, // → (E) | aH | i | f
		Z, // → λ
		Error // ошибочное состояние
	};

	enum class GeneratorTask
	{
		Empty,
		VariableId,
		IntNumber,
		FloatNumber,
		Read,
		Write,
		Plus,
		Minus,
		Multiply,
		Divide,
		Less,
		Assign,
		More,
		Equal,
		LessOrEqual,
		MoreOrEqual,
		NotEqual,
		Index,
		Task1,
		Task2,
		Task3,
		Task4,
		Task5,
		Task6,
		Task7,
		Task8,
		Task9,
		Task10,
		Task11,
	};

	struct MagazineItem
	{
		bool is_terminal;
		lexemeType lexeme;
		State state;

		MagazineItem(lexemeType l) {
			is_terminal = true;
			lexeme = l;
			state = State::Error;
		}

		MagazineItem(State s) {
			is_terminal = false;
			lexeme = lexemeType::Error;
			state = s;
		}
	};

	GeneratorTask current_task;
	lexeme current_lexeme;
	State current_state;
	table current_table;
	string last_array_name;
	stack<MagazineItem> Magazine;
	stack<GeneratorTask> Generator;
	stack<int> Marks;
	InterpretData data;

	vector<lexeme> input_data;
};

