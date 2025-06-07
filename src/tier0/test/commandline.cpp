#include <cstdio>
#include <dlfcn.h>
#include <string>


class ICommandLine {
public:
	virtual void CreateCmdLine( const char* commandline ) = 0;
	virtual void CreateCmdLine( int argc, char** argv ) = 0;
	[[nodiscard]]
	virtual const char* GetCmdLine() const = 0;

	virtual const char* CheckParm( const char* psz, const char** ppszValue = nullptr ) const = 0;
	virtual void RemoveParm( const char* parm ) = 0;
	virtual void AppendParm( const char* pszParm, const char* pszValues ) = 0;

	virtual const char* ParmValue( const char* psz, const char* pDefaultVal = nullptr ) const = 0;
	virtual int ParmValue( const char* psz, int nDefaultVal ) const = 0;
	virtual float ParmValue( const char* psz, float flDefaultVal ) const = 0;

	[[nodiscard]]
	virtual int ParmCount() const = 0;
	virtual int FindParm( const char* psz ) const = 0;
	[[nodiscard]]
	virtual const char* GetParm( int nIndex ) const = 0;

	virtual void SetParm( int nIndex, char const* pNewParm ) = 0;

	virtual const char* ParmValueByIndex( int nIndex, const char* pDefaultVal = nullptr ) const = 0;
};

auto doTest( int argc, char** argv, const char* pLibrary ) -> void {
	std::printf( "\n--- TESTING `%s` TESTING ---\n", pLibrary );

	const auto handle = dlopen( pLibrary, RTLD_NOW );
	std::printf( "dlopen=`%s`, handle=`%p`\n", dlerror(), handle );
	const auto CommandLine_Tier0 = reinterpret_cast<ICommandLine* (*) ()>( dlsym( handle, "CommandLine_Tier0" ) );
	std::printf( "dlsym=`%s`, func=`%p`\n", dlerror(), reinterpret_cast<void*>( CommandLine_Tier0 ) );

	const auto cmd = CommandLine_Tier0();

	cmd->CreateCmdLine( argc, argv );
	std::printf( "cmdline=`%s`\n", cmd->GetCmdLine() );

	std::printf( "GetParm(0)=`%s`\n", cmd->GetParm( 0 ) );

	cmd->AppendParm( "-game", "mod_hl2mp" );
	std::printf( "AppendParm('-game', 'mod_hl2mp')=`%s`\n", cmd->GetCmdLine() );

	cmd->RemoveParm( "-game" );
	std::printf( "RemoveParm('-game')=`%s`\n", cmd->GetCmdLine() );

	cmd->RemoveParm( "-game" );
	std::printf( "RemoveParm('-game')=`%s`\n", cmd->GetCmdLine() );

	cmd->AppendParm( "-dev", nullptr );
	std::printf( "AppendParm('-dev', nullptr)=`%s`\n", cmd->GetCmdLine() );

	cmd->AppendParm( "-dov", nullptr );
	std::printf( "AppendParm('-dov', nullptr)=`%s`\n", cmd->GetCmdLine() );

	cmd->AppendParm( "-dev", nullptr );
	std::printf( "AppendParm('-dev', nullptr)=`%s`\n", cmd->GetCmdLine() );

	cmd->RemoveParm( "-dev" );
	std::printf( "RemoveParm('-dev')=`%s`\n", cmd->GetCmdLine() );

	dlclose( handle );
}


int main( const int argc, char** const argv ) {
	for ( int i{ 0 }; i < argc; i += 1 ) {
		std::printf( "argc=`%d`, argv[i]=`%s`\n", i, argv[i] );
	}

	doTest( argc, argv, "../libtier0.so" );
	doTest( argc, argv, "../libtier02.so" );

	return 0;
}
