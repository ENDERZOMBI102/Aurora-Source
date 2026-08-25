//
// Created by ENDERZOMBI102 on 09/02/2024.
//
#include "commandline.hpp"
#include "dbg.h"


namespace {
	CCommandLine s_pCommandLine{};
	constexpr size_t MAX_ARGSBUFFER_LEN{ 256 };
	char s_ArgsBuffer[MAX_ARGSBUFFER_LEN] { };

	auto tokenize( const char* line, std::string& buffer ) -> const char* {
		// if we're already at the end, do nothing
		if ( not line or *line == '\0' ) {
			return nullptr;
		}

		// ignore leading space
		while ( *line == ' ' or *line == '\t' ) {
			line += 1;
		}

		size_t offset;
		const char* start;
		if ( ( offset = *line == '"' ) ) {  // parse a quoted string
			start = ++line;
			while ( *line != '"' and *line != '\0' ) {
				line += 1;
			}
		} else {  // parse a single token
			start = line;
			while ( *line != ' ' and *line != '\t' and *line != '\0' ) {
				line += 1;
			}
		}

		buffer.clear();
		buffer.append( start, line - start );
		// return the new initial position
		return line + offset;
	}
}

auto CCommandLine::CreateCmdLine( const char* pCommandLine ) -> void {
	this->Reset();
	// allocates new cmdline
	const char* line{ pCommandLine };
	std::string token;
	while ( (line = tokenize( line, token )) ) {
		m_Params.emplace_back( token );
		m_CmdLine += token + " ";
	}

	m_CmdLine.resize( m_CmdLine.length() - 1 );
	m_CmdLine.shrink_to_fit();
}
auto CCommandLine::CreateCmdLine( const int argc, char** argv ) -> void {
	using namespace std::string_literals;
	this->Reset();
	// allocates new cmdline, wrapping every token in `"`
	for ( int i{ 0 }; i < argc; i += 1 ) {
		m_Params.emplace_back( argv[ i ] );
		m_CmdLine += "\""s + argv[i] + "\" ";
	}
	m_CmdLine.resize( m_CmdLine.length() - 1 );
	m_CmdLine.shrink_to_fit();
}
auto CCommandLine::GetCmdLine() const -> const char* {
	// returns our version of the cmdline
	return m_CmdLine.c_str();
}

auto CCommandLine::CheckParm( const char* psz, const char** ppszValue ) const -> const char* {
	const int index{ this->FindParm( psz ) };
	if ( ppszValue ) {
		*ppszValue = nullptr;
	}

	if ( not index ) {
		return nullptr;
	}

	if ( ppszValue and index + 1 < m_Params.size() and m_Params[index + 1][0] != '-' and m_Params[index + 1][0] != '+' ) {
		*ppszValue = m_Params[index + 1].c_str();
	}
	return m_Params[index].c_str();
}
auto CCommandLine::RemoveParm( const char* parm ) -> void {
	// possibly remove `-key` and its `value`
	bool exists{};
	for ( int i{}; i < m_Params.size(); i += 1 ) {
		if ( m_Params[i] == parm ) {
			exists = true;
			// remove from params vector
			m_Params.erase( m_Params.begin() + i );
			if ( i < m_Params.size() and (m_Params[i][0] != '-' or m_Params[i][0] != '+') ) {
				m_Params.erase( m_Params.begin() + i );
			}
			break;
		}
	}
	if ( not exists ) {
		return;
	}

	if ( size_t pos = m_CmdLine.find( parm ); pos != std::string::npos ) {
		size_t end{ pos };
		while ( end < m_CmdLine.size() ) {
			end += 1;
			// if we next another parm or eoi, end loop
			if ( m_CmdLine[end] == '\0' ) {
				break;
			}
			if ( m_CmdLine[end] == '-' || m_CmdLine[end] == '+' ) {
				end -= 1;
				break;
			}
		}
		if ( pos != 0 ) [[likely]] {
			// -1 because we remove the beforehand space too
			pos -= 1;
		}
		m_CmdLine.erase( m_CmdLine.begin() + pos, m_CmdLine.begin() + end );
	}
}
auto CCommandLine::AppendParm( const char* pszParm, const char* pszValues ) -> void {
	// appends to the cmdline string without wrapping in `"`; but first removes it if it exists
	this->RemoveParm( pszParm );

	m_Params.emplace_back( pszParm );
	m_CmdLine.append( " " ).append( pszParm );

	// FIXME: This has invalid behavior, it doesn't parse the param correctly.
	if ( pszValues ) {
		m_Params.emplace_back( pszValues );
		m_CmdLine.append( " " ).append( pszValues );
	}
}

auto CCommandLine::ParmValue( const char* psz, const char* pDefaultVal ) const -> const char* {
	for ( int i{ 0 }; i < m_Params.size(); i += 1 ) {
		if ( m_Params[i] == psz and i + 1 < m_Params.size() ) {
			return m_Params[ i + 1 ].c_str();
		}
	}
	return pDefaultVal;
}
auto CCommandLine::ParmValue( const char* psz, const int nDefaultVal ) const -> int {
	for ( int i{ 0 }; i < m_Params.size(); i += 1 ) {
		if ( m_Params[i] == psz && i + 1 < m_Params.size() ) {
			char* invalid;
			const auto value{ strtol( m_Params[ i + 1 ].c_str(), &invalid, 10 ) };
			if ( invalid ) {
				break;
			}

			return value;
		}
	}
	return nDefaultVal;
}
auto CCommandLine::ParmValue( const char* psz, const float flDefaultVal ) const -> float {
	for ( int i{ 0 }; i < m_Params.size(); i += 1 ) {
		if ( m_Params[i] == psz && i + 1 < m_Params.size() ) {
			char* invalid;
			const auto value{ strtof( m_Params[ i + 1 ].c_str(), &invalid ) };
			if ( invalid ) {
				break;
			}

			return value;
		}
	}
	return flDefaultVal;
}

auto CCommandLine::ParmCount() const -> int {
	// counting both `-key`s and `value`s
	return static_cast<int>( m_Params.size() );
}
auto CCommandLine::FindParm( const char* psz ) const -> int {
	// ignores wrapping
	for ( int i{ 0 }; i < m_Params.size(); i += 1 ) {
		if ( m_Params[i] == psz ) {
			return i;
		}
	}
	return 0;
}
auto CCommandLine::GetParm( const int nIndex ) const -> const char* {
	if ( m_Params.size() < nIndex ) {
		return "";
	}

	return m_Params[nIndex].c_str();
}

auto CCommandLine::SetParm( const int nIndex, const char* pNewParm ) -> void {
	if ( m_Params.size() < nIndex ) {
		return;
	}

	m_Params[nIndex] = pNewParm;
}

auto CCommandLine::ParmValueByIndex( const int nIndex, const char* pDefaultVal ) const -> const char* {
	if ( nIndex == 0 or nIndex >= m_Params.size() ) {
		return pDefaultVal;
	}

	return m_Params[nIndex + 1].c_str();
}

auto CCommandLine::Reset() -> void {
	m_CmdLine.clear();
	m_Params.clear();
}

auto BuildCmdLine( const int pArgc, const char** pArgv, const bool pSteam ) -> void* {
	size_t used{};
	char* buffer{ s_ArgsBuffer };
	for ( int i{}; i < pArgc; i += 1 ) {
		const char* string{ pArgv[i] };

		const size_t len{ strlen( string ) };
		if ( used + len + 1 >= MAX_ARGSBUFFER_LEN ) {
			printf( "[BuildCmdLine] Given more than storage! max is %u", MAX_ARGSBUFFER_LEN ); // NOLINT(*-use-std-print)
			break;
		}

		memcpy( buffer + used, string, len );
		used += len;
		buffer[used] = ' ';
		used += 1;
	}

	if ( pSteam ) {
		strcpy( buffer + used, "-steam" );
		used += 6;
	}
	buffer[used] = '\0';

	return s_ArgsBuffer;
}


auto CommandLine_Tier0() -> ICommandLine* {
	return &s_pCommandLine;
}
