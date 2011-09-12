cmake_minimum_required(VERSION 2.8)

include(${PROJECT_SOURCE_DIR}/script/macro.txt)

include(${QT_USE_FILE})

set (LIBNAME ruleSystem)
set (SOURCES
		action.cpp
		calculator.cpp
		calculatorfactory.cpp
		constant.cpp
		dbwrapper.cpp
		element.cpp
		evaluatable.cpp
		feature.cpp
		function.cpp
		rule_defaults.cpp
		type.cpp
)

set (HEADERS
	action.hpp
	calculator.hpp
	calculatorfactory.hpp
	constant.hpp
	dbwrapper.hpp
	element.hpp
	evaluatable.hpp
	exception.hpp
	feature.hpp
	function.hpp
	idb.hpp
	ielementlistener.hpp
	rule_defaults.hpp
	type.hpp
)
set (Q_MOC_HPP )
set (Q_UI )
set (Q_RES )
set (SUBDIRECTORIES
	graphicsView
	util
	serialization
	prolog
)

set (LIBRARIES)


INCLUDE_ALL_QT_SUBDIRECTORIES_HEADER_SOURCES(SUBDIRECTORIES)

QT4_WRAP_CPP(HWQ_MOC_CPP ${Q_MOC_HPP})
QT4_WRAP_UI(HWQ_UI_CPP ${Q_UI})
QT4_ADD_RESOURCES(HWQ_RES_H ${Q_RES})

include_directories(${CMAKE_CURRENT_BINARY_DIR} . ${MY_INCLUDE_DIRS})

list(APPEND SOURCES ${HWQ_MOC_CPP} ${HWQ_UI_CPP} ${HWQ_RES_H})
list(APPEND LIBRARIES ${QT_LIBRARIES} )

foreach(lang ${LANGUAGES})
	set(in_trans_file ${TRANSLATION_DIR}/${LIBNAME}_${lang}.ts)
	qt4_create_translation(QM ${SOURCES} ${HEADERS} ${in_trans_file})
endforeach(lang)

set(QM ${TRANSLATION_DIR}/ruleSystem_nl_BE.qm)
file(COPY ${QM} DESTINATION ${CMAKE_BINARY_DIR}/bin)

add_custom_target(${LIBNAME}_trans DEPENDS ${QM})
add_dependencies(update_translations ${LIBNAME}_trans)

add_library ( ${LIBNAME} STATIC ${SOURCES} ${HEADERS})
target_link_libraries( ${LIBNAME} ${LIBRARIES} )

install (TARGETS ${LIBNAME} DESTINATION lib)
INSTALL_HEADERS_WITH_DIRECTORY(${LIBNAME} HEADERS)

set_target_properties(${LIBNAME} PROPERTIES translation_file ${QM})
