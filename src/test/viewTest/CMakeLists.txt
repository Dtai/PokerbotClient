
find_package(Qt4 REQUIRED)
set(QT_USE_QTTEST TRUE)
include(${QT_USE_FILE})

set(CMAKE_CXX_FLAGS "-g -ggdb -Wall")

set (PROGNAME viewTest)

set (SOURCES
	main.cpp
	mainwindow.cpp
	)

set (HEADERS
	mainwindow.hpp
)

set (Q_MOC_HPP
	mainwindow.hpp
)

set (Q_UI
	mainwindow.ui
)
set (Q_RES )
set (LIBRARIES )

QT4_WRAP_CPP(HWQ_MOC_CPP ${Q_MOC_HPP})
QT4_WRAP_UI(HWQ_UI_CPP ${Q_UI})
QT4_ADD_RESOURCES(HWQ_RES_H ${Q_RES})

include_directories(${CMAKE_CURRENT_BINARY_DIR} .)

list(APPEND SOURCES ${HWQ_MOC_CPP} ${HWQ_UI_CPP} ${HWQ_RES_H})
list(APPEND LIBRARIES ${QT_LIBRARIES} )

add_executable(${PROGNAME} ${SOURCES} ${HEADERS})
target_link_libraries( ${PROGNAME} ${LIBRARIES} ruleSystem pokerRuleSystem)





