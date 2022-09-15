#pragma once
#include<string>
#include"Program.h"
#include"array.h"

namespace global {
	extern int m_size_lenta;
	extern int m_size_rule;
}

class TuringMachine{
private:
	Program* m_instruction;
	unsigned int m_maxsteps;
	int m_size_rule;
public:
	TuringMachine() : m_instruction(nullptr), m_maxsteps(0), m_size_rule(0) {};
	TuringMachine(Program* instruction, unsigned int maxsteps) : m_instruction(instruction), m_maxsteps(maxsteps),
			m_size_rule(global::m_size_rule) {};
	TuringMachine(const TuringMachine& X) : m_maxsteps(X.m_maxsteps), m_size_rule(X.m_size_rule) {
		m_instruction = new Program[m_size_rule];
		for (size_t i = 0; i < (unsigned int)m_size_rule; ++i) {
			m_instruction[i].m_initial_state = X.m_instruction[i].m_initial_state;
			m_instruction[i].m_initial_symbol = X.m_instruction[i].m_initial_symbol;
			m_instruction[i].m_next_state = X.m_instruction[i].m_next_state;
			m_instruction[i].m_next_symbol = X.m_instruction[i].m_next_symbol;
			m_instruction[i].m_direction = X.m_instruction[i].m_direction;
		}
	}
	~TuringMachine() {
		delete[] m_instruction;
		m_instruction = nullptr;
	}
	TuringMachine& operator=(const TuringMachine& X);

	std::string calc(std::string const& init, int maxsteps);

	unsigned int change_slide(Array&, unsigned int slide, unsigned int num_instr);

	int search_another_instr(unsigned int, unsigned int);

	int search_instr(unsigned int, unsigned int);

	int to_output(std::string, char*);

	friend Program;
	friend Array;
};