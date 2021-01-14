#include <stack>
#include <stdexcept>
#include <iostream>
#include "ops_interpreter.h"

using namespace std;

ops_interpreter::ops_interpreter(InterpretData data) {
	input_data = data;
}

int ops_interpreter::GetInt(OpsItem& item) {
	if (item.type == OpsItemType::IntNumber)
	{
		return item.int_num;
	}
	else if (input_data.int_table.count(item.var_name))
	{
		return input_data.int_table[item.var_name];
	}
	else if (input_data.arrayInt_table.count(item.var_name))
	{
		return input_data.arrayInt_table[item.var_name][item.int_num];
	}
	else
	{
		string msg = "Interpreter error; int variable or int number was expected; line = "
			+ to_string(item.line) + ", pos = " + to_string(item.pos);
		throw runtime_error(msg);
	}
}

double ops_interpreter::GetFloat(OpsItem& item) {
	if (item.type == OpsItemType::FloatNumber)
	{
		return item.float_num;
	}
	else if (input_data.float_table.count(item.var_name))
	{
		return input_data.float_table[item.var_name];
	}
	else if (input_data.arrayFloat_table.count(item.var_name))
	{
		return input_data.arrayFloat_table[item.var_name][item.int_num];
	}
	else
	{
		string msg = "Interpreter error; float variable or float number was expected; line = "
			+ to_string(item.line) + ", pos = " + to_string(item.pos);
		throw runtime_error(msg);
	}
}

void ops_interpreter::SetInt(OpsItem& item, int num) {
	if (input_data.int_table.count(item.var_name))
	{
		input_data.int_table[item.var_name] = num;
	}
	else if (input_data.arrayInt_table.count(item.var_name))
	{
		input_data.arrayInt_table[item.var_name][item.int_num] = num;
	}
	else
	{
		string msg = "Interpreter error; int variable was expected; line = "
			+ to_string(item.line) + ", pos = " + to_string(item.pos);
		throw runtime_error(msg);
	}
}

void ops_interpreter::SetFloat(OpsItem& item, double num) {
	if (input_data.float_table.count(item.var_name))
	{
		input_data.float_table[item.var_name] = num;
	}
	else if (input_data.arrayFloat_table.count(item.var_name))
	{
		input_data.arrayFloat_table[item.var_name][item.int_num] = num;
	}
	else
	{
		string msg = "Interpreter error; float variable was expected; line = "
			+ to_string(item.line) + ", pos = " + to_string(item.pos);
		throw runtime_error(msg);
	}
}

bool ops_interpreter::HasFloat(OpsItem& item) {
	return item.type == OpsItemType::FloatNumber ||
		input_data.float_table.count(item.var_name) ||
		input_data.arrayFloat_table.count(item.var_name);
}

void ops_interpreter::run()
{
	stack<OpsItem> magazine;
	auto& ops = input_data.ops;
	auto& int_table = input_data.int_table;
	auto& float_table = input_data.float_table;
	auto& arrayInt_table = input_data.arrayInt_table;
	auto& arrayFloat_table = input_data.arrayFloat_table;

	for (size_t i = 0; i < ops.size(); ++i)
	{
		switch (ops[i].type)
		{
		case OpsItemType::VariableName:
		{
			if (!int_table.count(ops[i].var_name) &&
				!arrayInt_table.count(ops[i].var_name) &&
				!float_table.count(ops[i].var_name) &&
				!arrayFloat_table.count(ops[i].var_name))
			{
				string msg = "Interpreter error; Unknown variable; line = "
					+ to_string(ops[i].line) + ", pos = " + to_string(ops[i].pos);
				throw runtime_error(msg);
			}
			magazine.push(ops[i]);
			break;
		}
		case OpsItemType::IntNumber:
		case OpsItemType::FloatNumber:
		{
			magazine.push(ops[i]);
			break;
		}
		case OpsItemType::Operation:
		{
			switch (ops[i].operation)
			{
			case OpsItemOperation::Read:
			{
				auto a = magazine.top(); magazine.pop();

				if (HasFloat(a)) {
					double number;
					cin >> number;
					SetFloat(a, number);
				}
				else {
					int number;
					cin >> number;
					SetInt(a, number);
				}
				
				break;
			}
			case OpsItemOperation::Write:
			{
				auto a = magazine.top(); magazine.pop();

				if (HasFloat(a)) {
					cout << GetFloat(a) << endl;
				}
				else {
					cout << GetInt(a) << endl;
				}

				break;
			}
			case OpsItemOperation::Plus:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					int result;
					result = GetInt(a) + GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left + right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::Minus:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					int result;
					result = GetInt(a) - GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left - right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::Miltiply:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					int result;
					result = GetInt(a) * GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left * right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::Divide:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					int result;
					result = GetInt(a) / GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left / right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::Less:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					bool result;
					result = GetInt(a) < GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left < right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::Assign:
			{
				// a = b;
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (HasFloat(a)) {
					if (HasFloat(b)) {
						SetFloat(a, GetFloat(b));
					}
					else {
						SetFloat(a, double(GetInt(b)));
					}
				}
				else {
					if (HasFloat(b)) {
						SetInt(a, int(GetFloat(b)));
					}
					else {
						SetInt(a, GetInt(b));
					}
				}

				break;
			}
			case OpsItemOperation::More:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					bool result;
					result = GetInt(a) > GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left > right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::Equal:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					bool result;
					result = GetInt(a) == GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left == right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::LessOrEqual:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					bool result;
					result = GetInt(a) <= GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left <= right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::MoreOrEqual:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					bool result;
					result = GetInt(a) >= GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left >= right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::NotEqual:
			{
				auto b = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (!HasFloat(a) && !HasFloat(b)) {
					bool result;
					result = GetInt(a) != GetInt(b);
					magazine.emplace(result, a.line, a.pos);
				}
				else {
					double left, right;
					left = HasFloat(a) ? GetFloat(a) : GetInt(a);
					right = HasFloat(b) ? GetFloat(b) : GetInt(b);
					magazine.emplace(left != right, a.line, a.pos);
				}

				break;
			}
			case OpsItemOperation::Jump:
			{
				auto metka = magazine.top(); magazine.pop();

				i = GetInt(metka) - 1;
				break;
			}
			case OpsItemOperation::JumpIfFalse:
			{
				auto metka = magazine.top(); magazine.pop();
				auto a = magazine.top(); magazine.pop();

				if (GetInt(a) == 0) {
					i = GetInt(metka) - 1;
				}
				break;
			}
			case OpsItemOperation::Index:
			{
				auto idx = magazine.top(); magazine.pop();
				auto arr = magazine.top(); magazine.pop();

				arr.int_num = GetInt(idx);

				magazine.push(arr);
				break;
			}
			default:
			{
				string msg = "Interpreter error; Unknown operation; line = "
					+ to_string(ops[i].line) + ", pos = " + to_string(ops[i].pos);
				throw runtime_error(msg);
			}
			}
			break;
		}
		default:
		{
			string msg = "Interpreter error; Unknown ops item; line = "
				+ to_string(ops[i].line) + ", pos = " + to_string(ops[i].pos);
			throw runtime_error(msg);
		}
		}
	}
}