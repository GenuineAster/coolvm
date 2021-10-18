#pragma once

#include <cstdint>
#include <array>
#include <vector>

namespace CoolVM {
	enum class DataType : std::uint8_t {
		INT_64 = 0,
	};

	enum class Instruction : std::uint16_t {
		SET_INT_64 = 0,
		COMPARE_INT_64,
		ARITHMETIC_ADD_INT_64,

		COPY_INPUT_TO_STORE_INT_64,
		COPY_STORE_TO_OUTPUT_INT_64,
		COPY_RESULT_TO_STORE_INT_64,

		JUMP,
		JUMP_NOT_EQUAL,
		JUMP_EQUAL,
		JUMP_LESS,
		JUMP_LESS_EQUAL,
		JUMP_GREATER,
		JUMP_GREATER_EQUAL,
	};

	enum class MemoryType : std::uint8_t {
		INPUT = 0,
		OUTPUT,
		RESULT,
		STORE,
	};

	enum class CompareResults : std::uint8_t {
		EQUAL = 0,
		LESS = 1,
		GREATER = 2,
	};

	struct Operand {
		std::int64_t Index;
	};

	struct Operation {
		Instruction Instruction;
		std::array<Operand, 8> Operands;
	};

	struct DataStore {
		std::vector<std::int64_t> Data;
	};

	struct VMState {
		DataStore Inputs;
		DataStore Outputs;
		DataStore Result;
		DataStore Store;

		std::uint32_t OperationIndex = 0;
		CompareResults CompareResults = CompareResults::EQUAL;
	};

	void clear_state(VMState& state);

	struct Program {
		std::vector<Operation> Operations;
	};

	void run_program(VMState& state, const Program& program);
}
