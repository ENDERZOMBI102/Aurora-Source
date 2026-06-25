#
#
# Common Directories for CMake
#
#
if(POSIX)
	set(LIBCOMMON		${ROOT_DIR}/lib/common/linux32)
	set(LIBPUBLIC		${ROOT_DIR}/lib/public/linux32)
elseif(WIN32)
	set(LIBCOMMON		${ROOT_DIR}/lib/common)
	set(LIBPUBLIC		${ROOT_DIR}/lib/public)
endif()

set(THIRDPARTY_DIR 	${ROOT_DIR}/thirdparty)

set(PUBLIC_INCLUDE	${ROOT_DIR}/public)
set(COMMON_INCLUDE 	${ROOT_DIR}/common)
set(TIER0_INCLUDE	${PUBLIC_INCLUDE}/tier0)
set(TIER1_INCLUDE	${PUBLIC_INCLUDE}/tier1)
set(APPSYSTEM_INCLUDE	${PUBLIC_INCLUDE}/appsystem)
set(TOGL_INCLUDE	${PUBLIC_INCLUDE}/togl)

set(DX9SDK			${ROOT_DIR}/dx9sdk/)
set(DX10SDK			${ROOT_DIR}/dx10sdk/)

# For LZMA
set(LZMA_INCLUDE	${COMMON_INCLUDE}/lzma)
set(LZMA_SRCS		${THIRDPARTY_DIR}/lzma)

link_directories(${LIBCOMMON} ${LIBPUBLIC})
include_directories(${PUBLIC_INCLUDE} ${COMMON_INCLUDE} ${TIER1_INCLUDE} ${TIER0_INCLUDE})
