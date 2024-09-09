//
// Created by ENDERZOMBI102 on 23/02/2024.
//
#pragma once
#include "ifsdriver.hpp"
#include "vpkpp/PackFile.h"


class CPackFsDriver : public IFsDriver {
public:
	// metadata
	CPackFsDriver( int32 pId, const char* pAbsolute, const char* pPath );
	[[nodiscard]] auto GetNativePath() const -> const char* override;
	[[nodiscard]] auto GetNativeAbsolutePath() const -> const char* override;
	[[nodiscard]] auto GetIdentifier() const -> int32 override;
	[[nodiscard]]
	auto GetType() const -> const char* override;
	auto Shutdown() -> void override;
	// file ops
	auto Open  ( const char* pPath, OpenMode pMode ) -> FileDescriptor* override;
	auto Read  ( const FileDescriptor* pDesc, void* pBuffer, uint32 pCount ) -> int32 override;
	auto Write ( const FileDescriptor* pDesc, const void* pBuffer, uint32 pCount ) -> int32 override;
	auto Flush ( const FileDescriptor* pDesc ) -> bool override;
	auto Close ( const FileDescriptor* pDesc ) -> void override;
	// generic ops
	auto Walk  ( const FileDescriptor* pDesc, const WalkEntry*& pEntry ) -> void override;
	auto Create( const char* pPath, FileType pType, OpenMode pMode ) -> FileDescriptor* override;
	auto Remove( const FileDescriptor* pDesc ) -> void override;
	auto Stat  ( const FileDescriptor* pDesc ) -> std::optional<StatData> override;
private:
	int32 m_iId;
	const char* m_szNativePath;
	std::unique_ptr<vpkpp::PackFile> m_PackFile;
	friend auto CreateSystemClient() -> IFsDriver*;
};