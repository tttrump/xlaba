#include <stdexcept>
#include "text_analyzer.h"

text_analyzer::text_analyzer(const string& pr_text) {
	program_text = pr_text;
	current_index = 0;
}

vector<lexeme> text_analyzer::get_data() {
	return data;
}

void text_analyzer::run() {
	lexeme cur_lexeme;
	int cur_line = 1;
	int cur_pos = 1;

	while (current_index < program_text.size()) {
		while (isspace(program_text[current_index])) {
			switch (program_text[current_index++]) {
			case ' ':
				++cur_pos;
				break;
			case '\n':
				++cur_line; cur_pos = 1;
				break;
			case '\t':
				cur_pos += 4;
				break;
			}
		}

		cur_lexeme = next_lexeme();
		cur_lexeme.line = cur_line;
		cur_lexeme.pos = cur_pos;

		if (cur_lexeme.lexeme_type == lexemeType::Error) {
			string msg = "Analyzer error; Value = '" + cur_lexeme.value + "', line = " + to_string(cur_line) + ", pos = " + to_string(cur_pos);
			throw runtime_error(msg);
		}

		cur_pos += cur_lexeme.value.size();

		data.push_back(cur_lexeme);
	}

	cur_lexeme.lexeme_type = lexemeType::Finish;
	cur_lexeme.line = cur_line;
	cur_lexeme.pos = cur_pos;
	data.push_back(cur_lexeme);
}

bool text_analyzer::ischar(char ch) {
	return ch == '_' || ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

lexeme text_analyzer::next_lexeme() {
	char cur_ch = program_text[current_index];
	current_index++;

	lexeme result;
	result.lexeme_type = lexemeType::Error;
	result.value = cur_ch;

	if (ischar(cur_ch)) {
		result.lexeme_type = lexemeType::Id;
		cur_ch = program_text[current_index];
		while (current_index < program_text.size() && ischar(cur_ch) || isdigit(cur_ch)) {
			result.value += cur_ch;
			current_index++;
			cur_ch = program_text[current_index];
		}
		if (result.value == "int") {
			result.lexeme_type = lexemeType::Int;
		}
		else if (result.value == "float") {
			result.lexeme_type = lexemeType::Float;
		}
		else if (result.value == "arrayInt") {
			result.lexeme_type = lexemeType::ArrayInt;
		}
		else if (result.value == "arrayFloat") {
			result.lexeme_type = lexemeType::ArrayFloat;
		}
		else if (result.value == "if") {
			result.lexeme_type = lexemeType::If;
		}
		else if (result.value == "else") {
			result.lexeme_type = lexemeType::Else;
		}
		else if (result.value == "while") {
			result.lexeme_type = lexemeType::While;
		}
		else if (result.value == "read") {
			result.lexeme_type = lexemeType::Read;
		}
		else if (result.value == "write") {
			result.lexeme_type = lexemeType::Write;
		}
	}
	else if (isdigit(cur_ch)) {
		result.lexeme_type = lexemeType::IntNumber;
		cur_ch = program_text[current_index];

		while (current_index < program_text.size() && isdigit(cur_ch)) {
			result.value += cur_ch;
			current_index++;
			cur_ch = program_text[current_index];
		}

		if (current_index < program_text.size() && ischar(cur_ch)) {
			while (current_index < program_text.size() && ischar(cur_ch)) {
				result.value += cur_ch;
				++current_index;
				cur_ch = program_text[current_index];
			}
			result.lexeme_type = lexemeType::Error;
		}

		if (current_index < program_text.size() && cur_ch == '.') {
			result.lexeme_type = lexemeType::FloatNumber;
			result.value += cur_ch;
			++current_index;
			cur_ch = program_text[current_index];
			while (current_index < program_text.size() && isdigit(cur_ch)) {
				result.value += cur_ch;
				current_index++;
				cur_ch = program_text[current_index];
			}
		}

		if (current_index < program_text.size() && ischar(cur_ch)) {
			while (current_index < program_text.size() && ischar(cur_ch)) {
				result.value += cur_ch;
				++current_index;
				cur_ch = program_text[current_index];
			}
			result.lexeme_type = lexemeType::Error;
		}
	}
	else if (cur_ch == '{') {
		result.lexeme_type = lexemeType::LeftBrace;
	}
	else if (cur_ch == '}') {
		result.lexeme_type = lexemeType::RightBrace;
	}
	else if (cur_ch == '[') {
		result.lexeme_type = lexemeType::LeftSquareBracket;
	}
	else if (cur_ch == ']') {
		result.lexeme_type = lexemeType::RightSquareBracket;
	}
	else if (cur_ch == '(') {
		result.lexeme_type = lexemeType::LeftRoundBracket;
	}
	else if (cur_ch == ')') {
		result.lexeme_type = lexemeType::RightRoundBracket;
	}
	else if (cur_ch == '+') {
		result.lexeme_type = lexemeType::Plus;
	}
	else if (cur_ch == '-') {
		result.lexeme_type = lexemeType::Minus;
	}
	else if (cur_ch == '*') {
		result.lexeme_type = lexemeType::Multiply;
	}
	else if (cur_ch == '/') {
		result.lexeme_type = lexemeType::Divide;
	}
	else if (cur_ch == ';') {
		result.lexeme_type = lexemeType::Semicolon;
	}
	else if (cur_ch == ',') {
		result.lexeme_type = lexemeType::Comma;
	}
	else if (cur_ch == '<') {
		result.lexeme_type = lexemeType::Less;
		if (current_index < program_text.size() && program_text[current_index] == '=') {
			current_index++;
			result.lexeme_type = lexemeType::LessOrEqual;
			result.value = "<=";
		}
	}
	else if (cur_ch == '=') {
		result.lexeme_type = lexemeType::Assign;
		if (current_index < program_text.size() && program_text[current_index] == '=') {
			current_index++;
			result.lexeme_type = lexemeType::Equal;
			result.value = "==";
		}
	}
	else if (cur_ch == '>') {
		result.lexeme_type = lexemeType::More;
		if (current_index < program_text.size() && program_text[current_index] == '=') {
			current_index++;
			result.lexeme_type = lexemeType::MoreOrEqual;
			result.value = ">=";
		}
	}
	else if (cur_ch == '!' && current_index < program_text.size() && program_text[current_index] == '=') {
	current_index++;
		result.lexeme_type = lexemeType::NotEqual;
		result.value = "!=";
	}

	return result;
}