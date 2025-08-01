# togl.cmake

set( TOGL_DIR "${CMAKE_CURRENT_LIST_DIR}/linuxwin" )
set( TOGL_SOURCE_FILES
	# DirectX Header Files
)

if ( ${USE_TOGL} )
	list( APPEND TOGL_SOURCE_FILES
		# Source Files
		"${TOGL_DIR}/dx9asmtogl2.cpp"
		"${TOGL_DIR}/dxabstract.cpp"
		"${TOGL_DIR}/glentrypoints.cpp"
		"${TOGL_DIR}/glmgr.cpp"
		"${TOGL_DIR}/glmgrbasics.cpp"
		$<${IS_OSX}:"${TOGL_DIR}/glmgrcocoa.mm">
		$<${IS_OSX}:"${TOGL_DIR}/intelglmallocworkaround.cpp">
		$<${IS_OSX}:"${TOGL_DIR}/mach_override.c">
		"${TOGL_DIR}/cglmtex.cpp"
		"${TOGL_DIR}/cglmfbo.cpp"
		"${TOGL_DIR}/cglmprogram.cpp"
		"${TOGL_DIR}/cglmbuffer.cpp"
		"${TOGL_DIR}/cglmquery.cpp"

		# Header Files
		"${TOGL_DIR}/dx9asmtogl2.h"
		"${TOGL_DIR}/glmgr_flush.inl"
		$<${IS_OSX}:"${TOGL_DIR}/intelglmallocworkaround.h">
		$<${IS_OSX}:"${TOGL_DIR}/mach_override.h">

		# Public Header Files
		"${SRCDIR}/public/togl/rendermechanism.h"
		"${SRCDIR}/public/togl/linuxwin/dxabstract.h"
		"${SRCDIR}/public/togl/linuxwin/dxabstract_types.h"
		"${SRCDIR}/public/togl/linuxwin/glbase.h"
		"${SRCDIR}/public/togl/linuxwin/glentrypoints.h"
		"${SRCDIR}/public/togl/linuxwin/glmgr.h"
		"${SRCDIR}/public/togl/linuxwin/glmdebug.h"
		"${SRCDIR}/public/togl/linuxwin/glmgrbasics.h"
		"${SRCDIR}/public/togl/linuxwin/glmgrext.h"
		"${SRCDIR}/public/togl/linuxwin/glmdisplay.h"
		"${SRCDIR}/public/togl/linuxwin/glmdisplaydb.h"
		"${SRCDIR}/public/togl/linuxwin/glfuncs.h"
		"${SRCDIR}/public/togl/linuxwin/cglmtex.h"
		"${SRCDIR}/public/togl/linuxwin/cglmfbo.h"
		"${SRCDIR}/public/togl/linuxwin/cglmprogram.h"
		"${SRCDIR}/public/togl/linuxwin/cglmbuffer.h"
		"${SRCDIR}/public/togl/linuxwin/cglmquery.h"
	)
endif ()

add_library( togl SHARED ${TOGL_SOURCE_FILES} )
set_target_properties( togl
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${GAMEDIR}/bin"
)

target_include_directories( togl
	PRIVATE
		"${SRCDIR}/public/togl/linuxwin"
)
link_to_bin( TARGET togl )

target_compile_definitions( togl
	PRIVATE
		serverplugin_emptyONLY
		TOGL_DLL_EXPORT
		PROTECTED_THINGS_ENABLE
		strncpy=use_Q_strncpy_instead
		_snprintf=use_Q_snprintf_instead
)

target_link_libraries( togl
	PRIVATE
		${ASRC_DR_tier0}  # may use reimpl or valve's based on -DASRC_USE_REIMPLS
		${ASRC_DR_vstdlib}
		tier1
		tier2
		mathlib
		SDL3::SDL3-shared
)
