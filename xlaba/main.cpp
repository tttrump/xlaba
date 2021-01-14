#include <iostream>
#include <fstream>
#include "text_analyzer.h"
#include "ops_generator.h"
#include "ops_interpreter.h"

using namespace std;

void run_program(string program_text) {
	try
	{
		text_analyzer textAnalyzer(program_text);
		textAnalyzer.run();

		ops_generator opsGenerator(textAnalyzer.get_data());
		opsGenerator.run();

		ops_interpreter opsInterpreter(opsGenerator.get_data());
		opsInterpreter.run();
	}
	catch (const exception& ex)
	{
		cerr << ex.what() << endl;
	}
}

void run_test() {
	cout << "expression test\n";
	int a, b, c;
	float d, e, f;
	a = 1;
	b = 2;
	c = 3;
	d = 4.4;
	e = 5.5;
	f = 6.6;
	a = (a + 1) * b - c;
	b = ((a * 2) * c * (b * 3)) / a;
	c = a + b * c - a - b;
	d = (f - e) * d - 3 * (2.0 - c);
	e = c - d * e;
	f = a + (b - c) / d - e * f;
	cout << "correct output:\n";
	cout << a << '\n' << b << '\n' << c << '\n' << d << '\n' << e << '\n' << f << '\n';

	string program_text;
	program_text += "int a, b, c;";
	program_text += "float d, e, f;";
	program_text += "a = 1;";
	program_text += "b = 2;";
	program_text += "c = 3;";
	program_text += "d = 4.4;";
	program_text += "e = 5.5;";
	program_text += "f = 6.6;";
	program_text += "a = (a + 1) * b - c;";
	program_text += "b = ((a * 2) * c * (b * 3)) / a;";
	program_text += "c = a + b * c - a - b;";
	program_text += "d = (f - e) * d - 3 * (2.0 - c);";
	program_text += "e = c - d * e;";
	program_text += "f = a + (b - c) / d - e * f;";
	program_text += "write(a);";
	program_text += "write(b);";
	program_text += "write(c);";
	program_text += "write(d);";
	program_text += "write(e);";
	program_text += "write(f);";
	
	cout << "program output:\n";
	run_program(program_text);
	cout << endl;
}

int main() {
	run_test();

	string file_name = "program.txt";
	ifstream pr = ifstream(file_name);
	string program_text;
	getline(pr, program_text, '\0');

	cout << "run main program:\n";
	run_program(program_text);
	cout << "finish main program:\n";

	return 0;
}