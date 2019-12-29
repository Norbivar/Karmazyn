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

	file(GLOB SFML_ALL_LIBS_DEBUG
		"${SFML_LIBRARIES}/*.lib"
	)
	file(GLOB SFML_ALL_LIBS_RELEASE
		"${SFML_LIBRARIES}/*.lib"
	)
	file(GLOB SFML_DEPS
		"${SFML_LIBRARIES}/*.lib"
	)
	LIST(FILTER SFML_DEPS EXCLUDE REGEX "sfml\-")
	if (${SFML_STATIC_LIBRARIES})
		message("Using staticly linked SFML.")
		LIST(FILTER SFML_ALL_LIBS_DEBUG INCLUDE REGEX "sfml\-[a-zA-Z]+\-s\-d\.lib")
		LIST(FILTER SFML_ALL_LIBS_RELEASE INCLUDE REGEX "sfml\-[a-zA-Z]+\-s\.lib")

		LIST(APPEND SFML_ALL_LIBS_DEBUG ${SFML_DEPS})
		LIST(APPEND SFML_ALL_LIBS_RELEASE ${SFML_DEPS}) # TODO: FIX THIS SHIT
		add_definitions(-DSFML_STATIC)
	else()
		message("Using dynamically linked SFML.")
		LIST(FILTER SFML_ALL_LIBS_DEBUG INCLUDE REGEX "sfml\-[a-zA-Z]+\-d\.lib")
		LIST(FILTER SFML_ALL_LIBS_RELEASE INCLUDE REGEX "sfml\-[a-zA-Z]+\.lib")
	endif()
	message("VN: SFML: ${SFML_ALL_LIBS_RELEASE}")
else()
	 message(FATAL_ERROR "Could not find SFML lib dir!")
endif()