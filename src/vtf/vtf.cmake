# vtf.cmake

set( VTF_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( VTF_SOURCE_FILES
	"${VTF_DIR}/cvtf.cpp"

	# Private Header files
	"${VTF_DIR}/cvtf.hpp"

	# Public Header Files
	"${SRC_DIR}/public/vtf/vtf.h"
)

add_library( vtf2 STATIC ${VTF_SOURCE_FILES} )
target_link_libraries( vtf2
	PRIVATE
		asrc::dr::tier0  # may use reimpl or valve's based on -DASRC_USE_REIMPLS
		mathlib
		asrc::dr::bitmap
		sourcepp::vtfpp
)

add_library( vtf IMPORTED STATIC )
set_target_properties( vtf
	PROPERTIES
		IMPORTED_LOCATION "${LIBPUBLIC}/vtf${CMAKE_STATIC_LIBRARY_SUFFIX}"
)

declare_replacement( vtf2 FOR vtf )
