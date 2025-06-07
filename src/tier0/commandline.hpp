//
// Created by ENDERZOMBI102 on 09/02/2024.
//
#pragma once

#include "tier0/icommandline.h"
#include <string>
#include <vector>

class CCommandLine : public ICommandLine {
public:
	auto CreateCmdLine( const char* pCommandLine ) -> void override;
	auto CreateCmdLine( int argc, char** argv ) -> void override;
	[[nodiscard]]
	auto GetCmdLine() const -> const char* override;

	// Check whether a particular parameter exists
	auto CheckParm( const char* psz, const char** ppszValue = nullptr ) const -> const char* override;
	auto RemoveParm( const char* parm ) -> void override;
	auto AppendParm( const char* pszParm, const char* pszValues ) -> void override;

	// Returns the argument after the one specified, or the default if not found
	auto ParmValue( const char* psz, const char* pDefaultVal = nullptr ) const -> const char* override;
	auto ParmValue( const char* psz, int nDefaultVal ) const -> int override;
	auto ParmValue( const char* psz, float flDefaultVal ) const -> float override;

	// Gets at particular parameters
	[[nodiscard]]
	auto ParmCount() const -> int override;
	auto FindParm( const char* psz ) const -> int override;  // Returns 0 if not found.
	[[nodiscard]]
	auto GetParm( int nIndex ) const -> const char* override;

	// copies the string passwed
	auto SetParm( int nIndex, char const* pNewParm ) -> void override;

	auto ParmValueByIndex( int nIndex, const char* pDefaultVal = nullptr ) const -> const char* override;
private:
	auto Reset() -> void;
private:
	// Compromise space for speed
	std::string m_CmdLine{};
	std::vector<std::string> m_Params{};
};

