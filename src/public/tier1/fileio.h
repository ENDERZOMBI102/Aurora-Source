//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: A collection of utility classes to simplify file I/O, and
//			as much as possible contain portability problems. Here avoiding 
//			including windows.h.
//
//=============================================================================

#ifndef FILEIO_H
#define FILEIO_H

#if defined (_WIN32)
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#endif

#include "tier0/platform.h"
#include "tier1/utlstring.h"
#include "tier1/utllinkedlist.h"

const int64 k_nMillion = 1000000;
const int64 k_nThousand = 1000;
const int64 k_nKiloByte = 1024;
const int64 k_nMegabyte = k_nKiloByte * k_nKiloByte;
const int64 k_nGigabyte = k_nMegabyte * k_nKiloByte;

class CPathString
{
public:

	// Constructors: Automatically fixes slashes and removes double slashes when the object is
	// constructed, and then knows how to append magic \\?\ on Windows for unicode paths
	CPathString( const char *pchUTF8Path );
	~CPathString();

	// Gets the path in UTF8
	const char *GetUTF8Path();

	// Gets wchar_t based path, with \\?\ pre-pended (allowing long paths on Win32, should only be used with unicode aware filesystem calls)
	const wchar_t *GetWCharPathPrePended();

private:

	void PopulateWCharPath();

	char *m_pchUTF8Path;
	wchar_t *m_pwchWideCharPathPrepended;

};

//-----------------------------------------------------------------------------
// Purpose: Encapsulates watching a directory for file changes
//-----------------------------------------------------------------------------
class CDirWatcher
{
public:
	CDirWatcher();
	~CDirWatcher();

	// only one directory can be watched at a time
	void SetDirToWatch( const char *pchDir );

	// retrieve any changes
	bool GetChangedFile( CUtlString *psFile );

#ifdef DBGFLAG_VALIDATE
	void Validate( CValidator &validator, const char *pchName );
#endif

private:
	CUtlLinkedList<CUtlString> m_listChangedFiles;
	void *m_hFile;
	void *m_pOverlapped;
	void *m_pFileInfo;
	friend class CDirWatcherFriend;

#if IsLinux()
	void AddFileToChangeList( const char *pchFile );
#endif
#if IsWindows()
	// used by callback functions to push a file onto the list
	void AddFileToChangeList( const char *pchFile );
	void PostDirWatch();
#endif
};

#endif // FILEIO_H
