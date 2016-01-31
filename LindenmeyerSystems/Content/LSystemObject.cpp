#include "pch.h"
#include "LSystemObject.h"

LindenmeyerSystems::LSystemObject::LSystemObject()
{
	m_axiom = "";
}

LindenmeyerSystems::LSystemObject::~LSystemObject()
{
}

void LindenmeyerSystems::LSystemObject::SetAxiom(std::string axiom)
{
	m_axiom = axiom;
}

void LindenmeyerSystems::LSystemObject::AddRuleMapping(char from, std::string to)
{
	m_rules[from] = to;
}

std::string LindenmeyerSystems::LSystemObject::ApplyRules(std::string instructions)
{
	size_t characterCount = instructions.length();

	std::string nextGeneration = "";
	for (int i = 0; i < characterCount; ++i)
	{
		char ruleFrom = instructions[i];
		if (m_rules.count(ruleFrom) == 1)
		{
			std::string ruleTo = m_rules[ruleFrom];
			nextGeneration.append(ruleTo);
		}
		else
		{
			char charAsCharString[2] = { ruleFrom, '\0' };
			nextGeneration.append(charAsCharString);
		}
	}

	return nextGeneration;
}

std::string LindenmeyerSystems::LSystemObject::ComputeGeneration(unsigned int generation)
{
	std::string resultString = m_axiom;

	for (unsigned int i = 0; i < generation; ++i)
	{
		resultString = ApplyRules(resultString);
	}

	return resultString;
}

void LindenmeyerSystems::LSystemObject::CacheInstructions(std::string instructions)
{
	m_instructions = instructions;
}

std::string LindenmeyerSystems::LSystemObject::GetCachedInstructions() const
{
	return m_instructions;
}
