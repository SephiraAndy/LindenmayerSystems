#pragma once

#include <map>

namespace LindenmeyerSystems
{
	enum class Instruction
	{
		DoNothing,
		DrawForward,
		LeanLeft,
		LeanRight,
		BendForward,
		BendBack,
		TwistAntiClockwise,
		TwistClockwise,
		OpenBranch,
		CloseBranch

		// TODO: More to add at a later time
		// ReduceThickness
		// AttachLeaf
	};

	class LSystemInterpreter
	{
	public:
		LSystemInterpreter();
		~LSystemInterpreter();
		void AddInstructionMapping(char, Instruction);

	private:
		std::map<char, Instruction> m_characterToInstructionMap;
		float m_leanDegrees;
		float m_bendDegrees;
		float m_twistDegrees;
	};
}