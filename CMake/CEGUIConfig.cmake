#set(FIND_SFML_PATHS
#    "${CMAKE_CURRENT_LIST_DIR}/../.."
#    ${SFML_ROOT}
#    $ENV{SFML_ROOT}
#    ~/Library/Frameworks
#    /Library/Frameworks
#    /usr/local
#    /usr
#    /sw
#    /opt/local
#    /opt/csw
#    /opt)

#find_path(SFML_ROOT_DIR SFML.tag
#          PATHS ${FIND_SFML_PATHS})

if (EXISTS "$ENV{CEGUI_ROOT}/include")
	set(CEGUI_INCLUDE_DIRS "$ENV{CEGUI_ROOT}/include/")
else()
	 message(FATAL_ERROR "Could not find CEGUI include dir!")
endif()
if (EXISTS "$ENV{CEGUI_ROOT}/lib")
	set(CEGUI_LIBRARIES "$ENV{CEGUI_ROOT}/lib/")
	if (EXISTS "$ENV{CEGUI_ROOT}/dependencies")
		if (EXISTS "$ENV{CEGUI_ROOT}/dependencies/include")
			set(CEGUI_INCLUDE_DIRS "${CEGUI_INCLUDE_DIRS}; $ENV{CEGUI_ROOT}/dependencies/include") # GL/GLEW.h is needed
		else()
			message(FATAL_ERROR "Could not find CEGUI_ROOT/dependencies/include dir!")
		endif()
	else()
		message(FATAL_ERROR "Could not find CEGUI_ROOT/dependencies dir!")
	endif()

	file(GLOB CEGUI_ALL_LIBS_DEBUG
		"${CEGUI_LIBRARIES}/*.lib"
	)
	file(GLOB CEGUI_ALL_LIBS_RELEASE
		"${CEGUI_LIBRARIES}/*.lib"
	)
	LIST(FILTER CEGUI_ALL_LIBS_DEBUG INCLUDE REGEX ".*_d.lib")
	LIST(FILTER CEGUI_ALL_LIBS_RELEASE EXCLUDE REGEX ".*_d.lib")
else()
	 message(FATAL_ERROR "Could not find CEGUI lib dir!")
endif()