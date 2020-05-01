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

	file(GLOB CEGUI_ALL_LIBS
		"${CEGUI_LIBRARIES}/*.lib"
	)
	if(${CEGUI_STATIC_LIBRARIES})
		message("Using staticly linked CEGUI.") # TODO: make this happen
		if(${CEGUI_DEBUG})
			LIST(FILTER CEGUI_ALL_LIBS INCLUDE REGEX ".*_d.lib")
		elseif()
			LIST(FILTER CEGUI_ALL_LIBS EXCLUDE REGEX ".*_d.lib")
		endif()
	else()
		message("Using dynamically linked CEGUI.")
		if(${CEGUI_DEBUG})
			LIST(FILTER CEGUI_ALL_LIBS INCLUDE REGEX ".*_d.lib")
		elseif()
			LIST(FILTER CEGUI_ALL_LIBS EXCLUDE REGEX ".*_d.lib")
		endif()
	endif()

else()
	 message(FATAL_ERROR "Could not find CEGUI lib dir!")
endif()