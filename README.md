# TuringMachine(Interpreter)
The file whose name is passed as the first argument contains strings of the form: 'q_i a_j -> q_k a_m d_n'(standard assignment for a turing machine).  
For example:  
q11 0 -> q10 0 L  
q11 1 -> q12 1 R  
q12 0 -> q13 0 R  
q12 1 -> q13 1 R  
q13 0 -> q11 0 R  
q13 1 -> q11 0 R  
The file whose name is passed to the program on the command line as the second argument specifies the size of the tape, the maximum number of clock cycles of the machine and the input information on the tape.
The name of file for result is passed as the third argument.
