#pragma once

#include <map>

namespace LindenmeyerSystems
{
	class LSystemObject
	{
	public:
		LSystemObject();
		~LSystemObject();

		void SetAxiom(std::string axiom);
		void AddRuleMapping(char from, std::string to);
		std::string ApplyRules(std::string instructions);
		std::string ComputeGeneration(unsigned int generation);
		void CacheInstructions(std::string);
		std::string GetCachedInstructions() const;

	private:
		std::string m_axiom;
		std::map<char, std::string> m_rules;
		std::string m_instructions;
	};
}