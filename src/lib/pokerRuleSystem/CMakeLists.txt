cmake_minimum_required(VERSION 2.8)

include(${PROJECT_SOURCE_DIR}/script/macro.txt)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set (LIBNAME pokerRuleSystem)
set (SOURCES
	booleanfunction.cpp
	numericalfunction.cpp
	simpledb.cpp
	pokerrulesystem.cpp
	pokeraction.cpp
	raiseaction.cpp
	types.cpp
)

set (HEADERS
	booleanfunction.hpp
	numericalfunction.hpp
	templatefunction.hpp
	simpledb.hpp
	pokerrulesystem.hpp
	pokeraction.hpp
	raiseaction.hpp
	types.hpp
	dictionary/featureDictionary.hpp
)
set (Q_MOC_HPP
	dictionary/featureDictionary.hpp
)
set (Q_UI )
set (Q_RES resources/pokerRes.qrc )
set (SUBDIRECTORIES
	graphicsView
	view
	serialization
	card
	prolog
)

set (LIBRARIES)


INCLUDE_ALL_QT_SUBDIRECTORIES_HEADER_SOURCES(SUBDIRECTORIES)

QT4_WRAP_CPP(HWQ_MOC_CPP ${Q_MOC_HPP})
QT4_WRAP_UI(HWQ_UI_CPP ${Q_UI})
QT4_ADD_RESOURCES(HWQ_RES_H ${Q_RES})

include_directories(${CMAKE_CURRENT_BINARY_DIR} . ${PROJECT_SOURCE_DIR}/src/lib ${MY_INCLUDE_DIRS})

list(APPEND SOURCES ${HWQ_MOC_CPP} ${HWQ_UI_CPP} ${HWQ_RES_H})
list(APPEND LIBRARIES ${QT_LIBRARIES} )
list(APPEND LIBRARIES ${Boost_LIBRARIES} )

foreach(lang ${LANGUAGES})
	set(in_trans_file ${TRANSLATION_DIR}/${LIBNAME}_${lang}.ts)
	qt4_create_translation(QM ${SOURCES} ${HEADERS} ${in_trans_file})
endforeach(lang)

set(QM ${TRANSLATION_DIR}/pokerRuleSystem_nl_BE.qm)
file(COPY ${QM} DESTINATION ${CMAKE_BINARY_DIR}/bin)

add_custom_target(${LIBNAME}_trans DEPENDS ${QM})
add_dependencies(update_translations ${LIBNAME}_trans)

add_library ( ${LIBNAME} STATIC ${SOURCES} ${HEADERS})
target_link_libraries( ${LIBNAME} ${LIBRARIES} ruleSystem)

install (TARGETS ${LIBNAME} DESTINATION lib)
INSTALL_HEADERS_WITH_DIRECTORY(${LIBNAME} HEADERS)

set_target_properties(${LIBNAME} PROPERTIES translation_file ${QM})
