find_package(Qt4 REQUIRED)
set(QT_USE_QTTEST TRUE)
set(QT_USE_QTNETWORK TRUE)
SET( QT_USE_QTWEBKIT TRUE )
include(${QT_USE_FILE})

#set(CMAKE_CXX_FLAGS "-g -ggdb -Wall")

set (PROGNAME ruleCreator)

 FIND_PATH(QT_QTWEBKIT_INCLUDE_DIR QtWebKit
		PATHS
		${QT_INCLUDE_DIR}/QtWebKit
		${QT_LIBRARY_DIR}/QtWebKit.framework/Headers
		NO_DEFAULT_PATH
		)

set (SOURCES
	main.cpp
	mainwindow.cpp
	rulewidget.cpp
	documentcontroller.cpp
	rulelistwidget.cpp
	settingsmanager.cpp
	settingsdialog.cpp
	connectiontarget.cpp	
	helpWindow.cpp
	welcomeWindow.cpp
	tab.cpp

	view/elementview.cpp
	view/garbagecanlabel.cpp
	view/predefinedrulesdescriptor.cpp
	view/predefinedelementview.cpp

	model/elementmodel.cpp
	model/predefinedelementmodel.cpp

	serialization/qt/ruleserialization.cpp

	network/helloSender.cpp
	network/codeSender.cpp

	config/reader.cpp
)

set (HEADERS
	mainwindow.hpp
	rulewidget.hpp
	documentcontroller.hpp
	rulelistwidget.hpp
	settingsmanager.hpp
	settingsdialog.hpp
    connectiontarget.hpp
	helpWindow.hpp
	welcomeWindow.hpp
	tab.hpp

	view/elementview.hpp
	view/garbagecanlabel.hpp
	view/predefinedrulesdescriptor.hpp
	view/predefinedelementview.hpp

	model/elementmodel.hpp
	model/predefinedelementmodel.hpp

	serialization/qt/ruleserialization.hpp

	network/helloSender.hpp
	network/codeSender.hpp

	config/reader.hpp
)

set (Q_MOC_HPP
	mainwindow.hpp
	rulewidget.hpp
	view/elementview.hpp
	view/garbagecanlabel.hpp
	view/predefinedrulesdescriptor.hpp
	view/predefinedelementview.hpp
	model/elementmodel.hpp
	model/predefinedelementmodel.hpp
	documentcontroller.hpp
	rulelistwidget.hpp
	settingsmanager.hpp
	settingsdialog.hpp
	helpWindow.hpp
	welcomeWindow.hpp
	network/helloSender.hpp
	network/codeSender.hpp
	config/reader.hpp
)

set (Q_UI
	mainwindow.ui
	rulewidget.ui
	settingsdialog.ui
	view/predefinedrulesdescriptor.ui
	helpWindow.ui
	welcomeWindow.ui
)
set (Q_RES
 resources/resources.qrc
)

set (LIBRARIES )

QT4_WRAP_CPP(HWQ_MOC_CPP ${Q_MOC_HPP})
QT4_WRAP_UI(HWQ_UI_CPP ${Q_UI})
QT4_ADD_RESOURCES(HWQ_RES_H ${Q_RES})

include_directories(${CMAKE_CURRENT_BINARY_DIR} .  ${MY_INCLUDE_DIRS})

list(APPEND SOURCES ${HWQ_MOC_CPP} ${HWQ_UI_CPP} ${HWQ_RES_H})
list(APPEND LIBRARIES ${QT_LIBRARIES} )

foreach(lang ${LANGUAGES})
	set(in_trans_file ${TRANSLATION_DIR}/${PROGNAME}_${lang}.ts)
	qt4_create_translation(QM_TMP2 ${SOURCES} ${HEADERS} ${in_trans_file})
endforeach(lang)

add_custom_target(${PROGNAME}_trans DEPENDS ${QM_TMP2})
add_dependencies(update_translations ${PROGNAME}_trans)

file(GLOB TRANSFILES ${TRANSLATION_DIR}/*.ts)
foreach(transFile ${TRANSFILES})
	qt4_add_translation(QM_TMP ${transFile})
	set(QM ${QM} ${QM_TMP})
endforeach(transFile)

add_executable(${PROGNAME} ${SOURCES} ${HEADERS} ${QM})
target_link_libraries( ${PROGNAME} ${LIBRARIES} ruleSystem pokerRuleSystem qjson)

file(COPY config.json DESTINATION ${CMAKE_BINARY_DIR}/bin)
