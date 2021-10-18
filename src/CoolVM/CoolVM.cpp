#include "CoolVM/CoolVM.hpp"

#include <iostream>

namespace CoolVM {
	constexpr bool c_Debug = false;

	void clear_state(VMState& state) {
		state.Inputs.Data.clear();
		state.Outputs.Data.clear();
		state.Result.Data.clear();
		state.Store.Data.clear();
		state.OperationIndex = 0;
	}

	void run_op(VMState& state, const Operation& op);

	void run_program(VMState& state, const Program& program) {
		while (state.OperationIndex < program.Operations.size()) {
			run_op(state, program.Operations[state.OperationIndex]);
			++state.OperationIndex;
		}
	}

	void debug_op(const Operation& op);

	void run_op(VMState& state, const Operation& op) {
		if (c_Debug) {
			debug_op(op);
		}

		switch (op.Instruction) {
		case Instruction::SET_INT_64: {
			state.Store.Data[op.Operands[0].Index] = op.Operands[1].Index;
		} break;
		case Instruction::COMPARE_INT_64: {
			const auto left =  state.Store.Data[op.Operands[0].Index];
			const auto right = state.Store.Data[op.Operands[1].Index];
			if (left == right) {
				state.CompareResults = CompareResults::EQUAL;
			} else if (left < right) {
				state.CompareResults = CompareResults::LESS;
			} else if (left > right) {
				state.CompareResults = CompareResults::GREATER;
			}
		} break;
		case Instruction::ARITHMETIC_ADD_INT_64: {
			state.Result.Data[0] = state.Store.Data[op.Operands[0].Index] + state.Store.Data[op.Operands[1].Index];
		} break;
		case Instruction::COPY_INPUT_TO_STORE_INT_64: {
			state.Store.Data[op.Operands[0].Index] = state.Inputs.Data[op.Operands[1].Index];
		} break;
		case Instruction::COPY_STORE_TO_OUTPUT_INT_64: {
			state.Outputs.Data[op.Operands[0].Index] = state.Store.Data[op.Operands[1].Index];
		} break;
		case Instruction::COPY_RESULT_TO_STORE_INT_64: {
			state.Store.Data[op.Operands[0].Index] = state.Result.Data[op.Operands[1].Index];
		} break;
		case Instruction::JUMP: {
			state.OperationIndex += op.Operands[0].Index;
		} break;
		case Instruction::JUMP_EQUAL: {
			if (state.CompareResults == CompareResults::EQUAL) {
				state.OperationIndex += op.Operands[0].Index;
			}
		} break;
		case Instruction::JUMP_NOT_EQUAL: {
			if ( ! (state.CompareResults == CompareResults::EQUAL)) {
				state.OperationIndex += op.Operands[0].Index;
			}
		} break;
		case Instruction::JUMP_LESS: {
			if (state.CompareResults == CompareResults::LESS) {
				state.OperationIndex += op.Operands[0].Index;
			}
		} break;
		case Instruction::JUMP_LESS_EQUAL: {
			if ((state.CompareResults == CompareResults::LESS) || (state.CompareResults == CompareResults::EQUAL)) {
				state.OperationIndex += op.Operands[0].Index;
			}
		} break;
		case Instruction::JUMP_GREATER: {
			if (state.CompareResults == CompareResults::GREATER) {
				state.OperationIndex += op.Operands[0].Index;
			}
		} break;
		case Instruction::JUMP_GREATER_EQUAL: {
			if ((state.CompareResults == CompareResults::GREATER) || (state.CompareResults == CompareResults::EQUAL)) {
				state.OperationIndex += op.Operands[0].Index;
			}
		} break;
		}
	}

	void debug_op(const Operation& op) {
		switch (op.Instruction) {
			case Instruction::SET_INT_64: {
				std::cout<<"set"<<std::endl;
			} break;
			case Instruction::COMPARE_INT_64: {
				std::cout<<"compare"<<std::endl;
			} break;
			case Instruction::ARITHMETIC_ADD_INT_64: {
				std::cout<<"add"<<std::endl;
			} break;
			case Instruction::COPY_INPUT_TO_STORE_INT_64: {
				std::cout<<"copy i2s"<<std::endl;
			} break;
			case Instruction::COPY_STORE_TO_OUTPUT_INT_64: {
				std::cout<<"copy s2o"<<std::endl;
			} break;
			case Instruction::COPY_RESULT_TO_STORE_INT_64: {
				std::cout<<"copy r2s"<<std::endl;
			} break;
			case Instruction::JUMP: {
				std::cout<<"jump"<<std::endl;
			} break;
			case Instruction::JUMP_EQUAL: {
				std::cout<<"jump e"<<std::endl;
			} break;
			case Instruction::JUMP_NOT_EQUAL: {
				std::cout<<"jump ne"<<std::endl;
			} break;
			case Instruction::JUMP_LESS: {
				std::cout<<"jump l"<<std::endl;
			} break;
			case Instruction::JUMP_LESS_EQUAL: {
				std::cout<<"jump le"<<std::endl;
			} break;
			case Instruction::JUMP_GREATER: {
				std::cout<<"jump g"<<std::endl;
			} break;
			case Instruction::JUMP_GREATER_EQUAL: {
				std::cout<<"jump ge"<<std::endl;
			} break;
		}
	}
}
