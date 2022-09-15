#pragma once

class Program {
public:
	unsigned int m_initial_state;
	unsigned int m_initial_symbol;
	unsigned int m_next_state;
	unsigned int m_next_symbol;
	char m_direction;
	Program() : m_initial_state(0), m_initial_symbol(0), m_next_state(0), m_next_symbol(0), m_direction(' '){};
	~Program() {};
};
