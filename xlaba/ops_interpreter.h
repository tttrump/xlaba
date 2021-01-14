#pragma once
#include "ops_generator.h"

class ops_interpreter {
public:
	void run();

	ops_interpreter(InterpretData);
private:
    int GetInt(OpsItem&);
	double GetFloat(OpsItem&);
    void SetInt(OpsItem&, int);
	void SetFloat(OpsItem&, double);
	bool HasFloat(OpsItem&);

	InterpretData input_data;
};
