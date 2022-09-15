#include<iostream>
#include<fstream>
#include"Program.h"

/*Program& Program::operator=(const Program& obj) {
	mt_instruction = obj.mt_instruction;
	mt_condition = obj.mt_condition;
	mt_output = obj.mt_output;
	mt_size = obj.mt_size;
	mt_maxsteps = obj.mt_maxsteps;
	mt_init = obj.mt_init;
	size_rule = obj.size_rule;
	delete[] mt_instructions;
	mt_instructions = new Rule[size_rule];
	for (size_t i = 0; i < size_rule; ++i) {
		mt_instructions[i].m_initial_state = obj.mt_instructions[i].m_initial_state;
		mt_instructions[i].m_initial_symbol = obj.mt_instructions[i].m_initial_symbol;
		mt_instructions[i].m_next_state = obj.mt_instructions[i].m_next_state;
		mt_instructions[i].m_next_symbol = obj.mt_instructions[i].m_next_symbol;
		mt_instructions[i].m_direction = obj.mt_instructions[i].m_direction;
	}
	return *this;
}

bool Program::get_instructions_from_file() {
	std::ifstream instruction(mt_instruction);
	mt_instructions = new Rule[0];
	while (instruction.peek() != EOF) {
		size_t i = 0;
		char str[256];
		int ch;
		while ((ch = instruction.get()) != '\n' && ch!=EOF) {
			str[i++] = (char)ch;
		}
		str[i] = '\0';
		if (CheckString(str)) {
			Rule* tmp = new Rule[size_rule+1];
			if (size_rule != 0) {
				for (size_t i = 0; i < size_rule; ++i) {
					tmp[i] = mt_instructions[i];
				}
			}
			delete[] mt_instructions;
			mt_instructions = tmp;
			++size_rule;
			size_t i = 1, k = 0;
			char state[256];
			while (str[i] != ' ') {
				state[k++] = str[i++];
			}
			state[k] = '\0';
			mt_instructions[size_rule-1].m_initial_state = atoi(state);
			mt_instructions[size_rule - 1].m_initial_symbol = str[++i] - '0';
			i += 6;
			char state1[256];
			k = 0;
			while (str[i] != ' ') {
				state1[k++] = str[i++];
			}
			state1[k] = '\0';
			mt_instructions[size_rule - 1].m_next_state = atoi(state1);
			++i;
			mt_instructions[size_rule - 1].m_next_symbol = str[i] - '0';
			i += 2;
			mt_instructions[size_rule - 1].m_direction = str[i];
		}
		else {
			return false;
		}
	}
}

bool Program::CheckString(char* str) {
	//before ->
	size_t i = 0;
	if (str[i++] != 'q') {
		ErrorToFile();
		return false;
	}
	size_t k = 0;
	while (str[i] >= '0' && str[i] <= '9') {
		++i; ++k;
	}
	if (k == 0 || str[i++] != ' ') {
		ErrorToFile();
		return false;
	}
	if (str[i] != '1' && str[i] != '0') {
		ErrorToFile();
		return false;
	}
	++i;
	// ->
	char tmp[5];
	for (size_t k = 0; k < 4; ++k, ++i) {
		tmp[k] = str[i];
	}
	tmp[4] = '\0';
	const char* for_compare = " -> ";
	if (strcmp(for_compare, tmp) != 0) {
		ErrorToFile();
		return false;
	}

	// after ->
	if (str[i++] != 'q') {
		ErrorToFile();
		return false;
	}
	k = 0;
	while (str[i] >= '0' && str[i] <= '9') {
		++i; ++k;
	}
	if (k == 0 || str[i++] != ' ') {
		ErrorToFile();
		return false;
	}
	if (str[i] != '1' && str[i] != '0') {
		ErrorToFile();
		return false;
	}
	i+=2;
	if (str[i] != 'L' && str[i] != 'R' && str[i] != 'N') {
		ErrorToFile();
		return false;
	}
	return true;
}

void Program::ErrorToFile() {
	std::ofstream output(mt_output);
	output << "Error";
}

void Program::get_conditions_from_file() {
	std::ifstream condition(mt_condition);
	if (!condition.is_open()) {
		std::cerr << "Can not open file <mt_condition>";
		return;
	}
	get_condition_argument(condition);
}

void Program::get_condition_argument(std::ifstream& condition) {
	char size[11];
	int ch;
	size_t i = 0;
	while ((ch = condition.get()) != ' ') {
		size[i++] = ch;
	}
	size[i] = '\0';
	mt_size = atoi(size);
	i = 0;
	char maxsteps[11];
	while ((ch = condition.get()) != ' ') {
		maxsteps[i++] = ch;
	}
	maxsteps[i] = '\0';
	mt_maxsteps = atoi(maxsteps);
	int ch1;
	while ((ch1 = condition.get()) != EOF && ch1!='\n') {
		mt_init += (char)ch1;
	}
}

char* Program::get_output_filename() const {
	return mt_output;
}
*/