/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <test/TestCase.h>

#include <libyul/optimiser/OptimiserStep.h>
#include <libyul/optimiser/NameDispenser.h>

#include <libyul/YulString.h>

#include <set>
#include <memory>

namespace solidity::langutil
{
class Scanner;
class Error;
using ErrorList = std::vector<std::shared_ptr<Error const>>;
}

namespace solidity::yul
{
struct AsmAnalysisInfo;
struct Block;
struct Dialect;
}

namespace solidity::yul::test
{

class YulOptimizerTest: public solidity::frontend::test::EVMVersionRestrictedTestCase
{
public:
	static std::unique_ptr<TestCase> create(Config const& _config)
	{
		return std::make_unique<YulOptimizerTest>(_config.filename);
	}

	explicit YulOptimizerTest(std::string const& _filename);

	TestResult run(std::ostream& _stream, std::string const& _linePrefix = "", bool const _formatted = false) override;

	void printSource(std::ostream& _stream, std::string const &_linePrefix = "", bool const _formatted = false) const override;
	void printUpdatedSettings(std::ostream &_stream, std::string const &_linePrefix = "", bool const _formatted = false) override;
	void printUpdatedExpectations(std::ostream& _stream, std::string const& _linePrefix) const override;

private:
	void printIndented(std::ostream& _stream, std::string const& _output, std::string const& _linePrefix = "") const;
	bool parse(std::ostream& _stream, std::string const& _linePrefix, bool const _formatted);
	void disambiguate();
	void updateContext();

	static void printErrors(std::ostream& _stream, langutil::ErrorList const& _errors);

	std::string m_source;
	std::string m_optimizerStep;
	std::string m_expectation;

	Dialect const* m_dialect = nullptr;
	std::set<YulString> m_reservedIdentifiers;
	std::unique_ptr<NameDispenser> m_nameDispenser;
	std::unique_ptr<OptimiserStepContext> m_context;

	std::shared_ptr<Block> m_ast;
	std::shared_ptr<AsmAnalysisInfo> m_analysisInfo;
	std::string m_obtainedResult;
};

}
