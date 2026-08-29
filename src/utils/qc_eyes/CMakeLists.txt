project( qc_eyes C CXX )

set( QC_EYES_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
        # Private Source/Header files
        "${QC_EYES_DIR}/QC_Eyes.cpp"
        "${QC_EYES_DIR}/QC_Eyes.h"
        "${QC_EYES_DIR}/QC_Eyes.rc"
        "${QC_EYES_DIR}/QC_EyesDlg.cpp"
        "${QC_EYES_DIR}/QC_EyesDlg.h"
        "${QC_EYES_DIR}/stdafx.cpp"
        "${QC_EYES_DIR}/stdafx.h"
        "${QC_EYES_DIR}/resource.h"

        # Resources
        "${QC_EYES_DIR}/res/eye_default.bmp"
        "${QC_EYES_DIR}/res/eye_lower_hi.bmp"
        "${QC_EYES_DIR}/res/eye_lower_lo.bmp"
        "${QC_EYES_DIR}/res/eye_lower_mid.bmp"
        "${QC_EYES_DIR}/res/eye_upper_hi.bmp"
        "${QC_EYES_DIR}/res/eye_upper_lo.bmp"
        "${QC_EYES_DIR}/res/eye_upper_mid.bmp"
        "${QC_EYES_DIR}/res/eye_XY_L.bmp"
        "${QC_EYES_DIR}/res/eye_XY_R.bmp"
        "${QC_EYES_DIR}/res/eye_Z_L.bmp"
        "${QC_EYES_DIR}/res/eye_Z_R.bmp"
        "${QC_EYES_DIR}/res/QC_Eyes.ico"
        "${QC_EYES_DIR}/res/QC_Eyes.rc2"
)

# Target type
set( KIND "EXEC" )
# Whether to set the exec's WIN32 flag
set( EXEC_WIN32 1 )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_precompile_headers( qc_eyes
    PRIVATE
        "${QC_EYES_DIR}/stdafx.h"
)

asource_compile_definitions(
    PRIVATE
        NO_WARN_MBCS_MFC_DEPRECATION
)
