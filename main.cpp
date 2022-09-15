#include<fstream>
#include"turingmachine.h"
#include<iostream>

bool CheckString(char*, char*);
bool strcmp(const char*, char*);

namespace global {
	int m_size_lenta=0;
	int m_size_rule=0;
}

int main(int argc, char* argv[]) {
	if(argc<4){
		std::cerr << "Program needs more arguments";
		return -2;
	}
	std::ifstream instruction(argv[1]);
	if (!instruction) {
		std::cerr << "Can not open file <instruction>";
		return -1;
	}
	std::ifstream condition(argv[2]);
	if (!condition) {
		std::cerr << "Can not open file <instruction>";
		return -1;
	}
	Program* instructions=new Program[0];
	unsigned int size_rule = 0;
	while (instruction.peek() != EOF) {
		size_t i = 0;
		char str[256];
		int ch;
		while ((ch = instruction.get()) != '\n' && ch != EOF) {
			str[i++] = (char)ch;
		}
		str[i] = '\0';
		if (CheckString(str,argv[3])) {
			Program* tmp = new Program[size_rule+1];
			if (size_rule != 0) {
				for (size_t i = 0; i < size_rule; ++i) {
					tmp[i] = instructions[i];
				}
			}
			instructions = nullptr;
			delete[] instructions;
			instructions = tmp;
			++size_rule;
			size_t i = 1, k = 0;
			char state[256];
			while (str[i] != ' ') {
				state[k++] = str[i++];
			}
			state[k] = '\0';
			instructions[size_rule - 1].m_initial_state = atoi(state);
			instructions[size_rule - 1].m_initial_symbol = str[++i] - '0';
			i += 6;
			char state1[256];
			k = 0;
			while (str[i] != ' ') {
				state1[k++] = str[i++];
			}
			state1[k] = '\0';
			instructions[size_rule - 1].m_next_state = atoi(state1);
			++i;
			instructions[size_rule - 1].m_next_symbol = str[i] - '0';
			i += 2;
			instructions[size_rule - 1].m_direction = str[i];
		}
		else {
			return -1;
		}
	}
	instruction.close();
	global::m_size_rule = size_rule;
	unsigned int size_lenta = 0;
	unsigned int maxsteps = 0;
	std::string init="";
	char size_lenta_[11];
	int ch;
	size_t i = 0;
	while ((ch = condition.get()) != ' ') {
		size_lenta_[i++] = ch;
	}
	size_lenta_[i] = '\0';
	size_lenta = atoi(size_lenta_);
	global::m_size_lenta = size_lenta;
	i = 0;
	char maxsteps_[11];
	while ((ch = condition.get()) != ' ') {
		maxsteps_[i++] = ch;
	}
	maxsteps_[i] = '\0';
	maxsteps = atoi(maxsteps_);
	int ch1;
	while ((ch1 = condition.get()) != EOF && ch1 != '\n') {
		init += (char)ch1;
	}
	condition.close();
	TuringMachine obj(instructions, maxsteps);
	obj.to_output(obj.calc(init, maxsteps), argv[3]);
	return 0;
}

bool CheckString(char* str, char* filename) {
	size_t i = 0;
	try {
		if (str[i++] != 'q')
			throw -1;
		size_t k = 0;
		while (str[i] >= '0' && str[i] <= '9') {
			++i; ++k;
		}
		if (k == 0 || str[i++] != ' ')
			throw -1;
		if (str[i] != '1' && str[i] != '0')
			throw -1;
		++i;
		char tmp[5];
		for (size_t k = 0; k < 4; ++k, ++i) {
			tmp[k] = str[i];
		}
		tmp[4] = '\0';
		const char* for_compare = " -> ";
		if (strcmp(for_compare, tmp) != 0)
			throw -1;
		if (str[i++] != 'q')
			throw -1;
		k = 0;
		while (str[i] >= '0' && str[i] <= '9') {
			++i; ++k;
		}
		if (k == 0 || str[i++] != ' ')
			throw -1;
		if (str[i] != '1' && str[i] != '0')
			throw -1;
		i += 2;
		if (str[i] != 'L' && str[i] != 'R' && str[i] != 'N')
			throw -1;
	}
	catch (...) {
			std::ofstream Output_stream(filename);
			if (!Output_stream){
				std::cerr << "Can not open file <output>";
				return false;
			}
			Output_stream << "Error";
			Output_stream.close();
			return false;
		}
	return true;
}

bool strcmp(const char* a, char* b) {
	size_t i = 0;
	while (a[i]==b[i] && a[i]!='\0') {
		++i;
	}
	if (i < 5) return false;
	return true;
}