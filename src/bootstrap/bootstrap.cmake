# bootstrap.cmake

set( BOOTSTRAP_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( BOOTSTRAP_SOURCE_FILES
	"${BOOTSTRAP_DIR}/main.cpp"
)

add_executable( bootstrap ${BOOTSTRAP_SOURCE_FILES} )

set_target_properties( bootstrap
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${GAMEDIR}/bin"
		RUNTIME_OUTPUT_NAME "aurosrc"
)

target_link_libraries( bootstrap
	PRIVATE
		${CMAKE_DL_LIBS}
		${ASRC_tier0}  # may use reimpl or valve's based on -DASRC_USE_REIMPLS
)
