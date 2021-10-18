#include <CoolVM/CoolVM.hpp>

#include <iostream>

int main() {
	CoolVM::VMState state;
	CoolVM::clear_state(state);

	state.Inputs.Data.resize(1024, 0);
	state.Outputs.Data.resize(1024, 0);
	state.Result.Data.resize(1024, 0);
	state.Store.Data.resize(1024, 0);

	CoolVM::Program program;
	program.Operations = {
		CoolVM::Operation{CoolVM::Instruction::COPY_INPUT_TO_STORE_INT_64, {0, 0}},
		CoolVM::Operation{CoolVM::Instruction::SET_INT_64, {1, 0}},
		CoolVM::Operation{CoolVM::Instruction::SET_INT_64, {2, 1}},
		CoolVM::Operation{CoolVM::Instruction::COMPARE_INT_64, {1, 0}},
		CoolVM::Operation{CoolVM::Instruction::JUMP_GREATER_EQUAL, {3}},
		CoolVM::Operation{CoolVM::Instruction::ARITHMETIC_ADD_INT_64, {1, 2}},
		CoolVM::Operation{CoolVM::Instruction::COPY_RESULT_TO_STORE_INT_64, {1, 0}},
		CoolVM::Operation{CoolVM::Instruction::JUMP, {-5}},
		CoolVM::Operation{CoolVM::Instruction::COPY_STORE_TO_OUTPUT_INT_64, {0, 1}},
	};

	state.Inputs.Data[0] = 1024*1024*1024;

	CoolVM::run_program(state, program);

	std::cout << state.Outputs.Data[0] << std::endl;

	return 0;
}
