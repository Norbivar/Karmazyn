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

	if (EXISTS "$ENV{SFML_ROOT}/include")
		set(SFML_INCLUDE_DIRS "$ENV{SFML_ROOT}/include/")
	else()
		 message(FATAL_ERROR "Could not find SFML include dir!")
	endif()
	if (EXISTS "$ENV{SFML_ROOT}/lib")
		set(SFML_LIBRARIES "$ENV{SFML_ROOT}/lib/")
		file(GLOB SFML_ALL_LIBS
			"${SFML_LIBRARIES}/*.lib"
		)
	else()
		 message(FATAL_ERROR "Could not find SFML lib dir!")
	endif()
