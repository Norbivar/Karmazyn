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

	if(WIN32)
		file(GLOB SFML_ALL_DLL
			"$ENV{SFML_ROOT}/bin/*.dll"
		)
		if(${SFML_DEBUG})
			LIST(FILTER SFML_ALL_DLL INCLUDE REGEX ".*-d-.*.dll")	
		else()
			LIST(FILTER SFML_ALL_DLL EXCLUDE REGEX ".*-d-.*.dll")	
		endif()
	endif()

	file(GLOB SFML_ALL_LIBS
		"${SFML_LIBRARIES}/*.lib"
	)
	file(GLOB SFML_DEPS
		"${SFML_LIBRARIES}/*.lib"
	)
	LIST(FILTER SFML_DEPS EXCLUDE REGEX "sfml\-")
	if (${SFML_STATIC_LIBRARIES})
		add_definitions(-DSFML_STATIC)
		message("Using staticly linked SFML.")
		if(${SFML_DEBUG})
			LIST(FILTER SFML_ALL_LIBS INCLUDE REGEX "sfml\-[a-zA-Z]+\-s\-d\.lib")
		else()
			LIST(FILTER SFML_ALL_LIBS INCLUDE REGEX "sfml\-[a-zA-Z]+\-s\.lib")
		endif()
		LIST(APPEND SFML_ALL_LIBS "${SFML_LIBRARIES}/sfml-main.lib")
		LIST(APPEND SFML_ALL_LIBS ${SFML_DEPS})
	else()
		message("Using dynamically linked SFML.")
		if(${SFML_DEBUG})
			LIST(FILTER SFML_ALL_LIBS INCLUDE REGEX "sfml\-[a-zA-Z]+\-d\.lib")
		else()
			LIST(FILTER SFML_ALL_LIBS INCLUDE REGEX "sfml\-[a-zA-Z]+\.lib")
		endif()
	endif()
else()
	 message(FATAL_ERROR "Could not find SFML lib dir!")
endif()