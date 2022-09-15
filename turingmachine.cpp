#include<iostream>
#include<fstream>
#include"turingmachine.h"

 TuringMachine& TuringMachine::operator=(const TuringMachine& X){
 if (this != &X) {
	 m_maxsteps = X.m_maxsteps;
	 m_size_rule = X.m_size_rule;
	 delete[] m_instruction;
	 m_instruction = new Program[m_size_rule];
	 for (size_t i = 0; i < (unsigned int)m_size_rule; ++i) {
		 m_instruction[i].m_initial_state = X.m_instruction[i].m_initial_state;
		 m_instruction[i].m_initial_symbol = X.m_instruction[i].m_initial_symbol;
		 m_instruction[i].m_next_state = X.m_instruction[i].m_next_state;
		 m_instruction[i].m_next_symbol = X.m_instruction[i].m_next_symbol;
		 m_instruction[i].m_direction = X.m_instruction[i].m_direction;
	 }
	}
 return *this;
}

std::string TuringMachine::calc(std::string const& init, int maxsteps) {
	Array for_exit;
	for_exit.copy_from_string(init);
	int num_instr = 0;
	unsigned int counter_ticks = 0;
	unsigned int statement = m_instruction[num_instr].m_initial_state;
	unsigned int condition = m_instruction[num_instr].m_initial_symbol;
	int slide = 0;
	while (counter_ticks < (unsigned int)maxsteps + 2) {
		unsigned int for_checking = 0;
		bool checking_slide = true;
		if (slide == -1 && for_exit.get_length() != global::m_size_lenta) {
			checking_slide = false;
			condition = 0;
		}
		else if (slide == -1 && for_exit.get_length() == global::m_size_lenta) {
			for_checking = global::m_size_lenta - 1;
			condition = for_exit[for_exit.get_length()-1]-'0';
		}
		else if (slide != -1 && slide == for_exit.get_length()) {
			checking_slide = false;
			condition = 0;
		}
		else {
			for_checking = slide;
			condition = for_exit[slide]-'0';
		}
		num_instr = search_instr(statement, condition);
		if (checking_slide && for_exit[for_checking] - '0' != condition) {
			num_instr = search_another_instr(statement, condition);
		}
		if (num_instr == -1) break;

		statement = m_instruction[num_instr].m_next_state;
		condition = m_instruction[num_instr].m_next_symbol;
		if (slide == for_exit.get_length()) {
			for_exit.push_end(condition);
		}
		else if (slide != -1 && slide != global::m_size_lenta) {
			for_exit.insert(condition, slide);
		}
		else if (slide == -1 && for_exit.get_length() != global::m_size_lenta) {
			for_exit.push_begin(condition);
		}
		else if (slide == -1 && for_exit.get_length() == global::m_size_lenta) {
			slide = global::m_size_lenta - 1;
			for_exit.insert(condition, global::m_size_lenta - 1);
		}
		else if (slide == global::m_size_lenta) {
			slide = 0;
			for_exit.insert(condition, 0);
		}
		slide = change_slide(for_exit,slide,num_instr);
		++counter_ticks;
	}
	if (counter_ticks > (unsigned int)maxsteps)
		return (std::string)"Not applicable";
	else
		return for_exit.to_string();
}

unsigned int TuringMachine::change_slide(Array& for_exit, unsigned int slide, unsigned int num_instr) {
	if (m_instruction[num_instr].m_direction == 'L' && slide == 0 && for_exit.get_length()==global::m_size_lenta)
		return global::m_size_lenta - 1;
	else if (m_instruction[num_instr].m_direction == 'R' && slide == global::m_size_lenta - 1)
		return 0;
	else if (m_instruction[num_instr].m_direction == 'L')
		return --slide;
	else if (m_instruction[num_instr].m_direction == 'R')
		return ++slide;
	else if (m_instruction[num_instr].m_direction == 'N' && slide == -1)
		return 0;
	else
		return slide;
}


int TuringMachine::search_another_instr(unsigned int statement, unsigned int condition) {
	size_t i = 0;
	for (size_t i = 0; i < (unsigned int)m_size_rule; ++i) {
		if (m_instruction[i].m_initial_state == statement
			&& m_instruction[i].m_initial_symbol != condition)
			return i;
	}
	return -1;
}

int TuringMachine::search_instr(unsigned int statement, unsigned int condition) {
	for (size_t i = 0; i < (unsigned int)m_size_rule; ++i) {
		if (m_instruction[i].m_initial_state == statement
			&& m_instruction[i].m_initial_symbol == condition)
			return i;
	}
	return -1;
}

int TuringMachine::to_output(std::string result, char* output_file) {
	std::ofstream Output_stream(output_file);
	if (!Output_stream) {
		std::cerr << "Can not open file <output>";
		return -1;
	}
	size_t i = 0;
	while (result[i] == '0')
		++i;
	while (i < result.length() && result[i] != '0' ) {
		Output_stream << result[i];
		++i;
	}
	Output_stream.close();
	return 0;
}