##| CMakeLists.txt build file
##| Author:  Jacob Alexander
##| Date:    December 28, 2009

cmake_minimum_required( VERSION 2.6.2 )
project( MHover )


#| DLL Sources
set( SRCS
	dll.cpp
	MHover.cpp
)


#| DLL Headers
set( HDRS
	MHover.h
)


#| DLL Name
set( LIB
	hoverlib
)


#| Libraries to Link
set( LIBS ${LIBS}
	user32.lib
)


#| Create Library
add_library( ${LIB} SHARED ${SRCS} )


#| Link Libraries to Library
target_link_libraries( ${LIB} ${LIBS} )



##| Executable

#| Executable Sources
set( SRCS_EXEC
	main.cpp
)

#| Executable Name
set( EXEC
	MHover
)

#| Create Executable
add_executable( ${EXEC} WIN32 ${SRCS_EXEC} )


#| Link Libraries to Executable
target_link_libraries( ${EXEC} ${LIBS} ${LIB} )

