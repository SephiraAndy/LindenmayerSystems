#include "pch.h"
#include "LSystemInterpreter.h"

LindenmeyerSystems::LSystemInterpreter::LSystemInterpreter() :
	m_leanDegrees(10.0f),
	m_bendDegrees(10.0f),
	m_twistDegrees(10.0f)
{
}

LindenmeyerSystems::LSystemInterpreter::~LSystemInterpreter()
{
}

void LindenmeyerSystems::LSystemInterpreter::AddInstructionMapping(char instructionCharacter, Instruction interpretation)
{
	m_characterToInstructionMap[instructionCharacter] = interpretation;
}
