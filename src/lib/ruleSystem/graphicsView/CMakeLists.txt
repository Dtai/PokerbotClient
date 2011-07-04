include(${PROJECT_SOURCE_DIR}/script/macro.txt)

set (SOURCES
	elementgraphicsitem.cpp
    elementfactory.cpp
    elementlayout.cpp
    functiongraphicsitem.cpp
    actiongraphicsitem.cpp
    elementgraphicsscene.cpp
    defaultitemdelegate.cpp
)

set (HEADERS
    elementgraphicsitem.hpp
    elementgraphicsscene.hpp
    elementfactory.hpp
    elementlayout.hpp
    functiongraphicsitem.hpp
    actiongraphicsitem.hpp
    elementitemdelegate.hpp
    defaultitemdelegate.hpp
)

set (Q_MOC_HPP 
	dndcontroller.hpp
	elementgraphicsscene.hpp
)

set (Q_UI )
set (Q_RES )
set (SUBDIRECTORIES )

#INCLUDE_ALL_QT_SUBDIRECTORIES_HEADER_SOURCES(${SUBDIRECTORIES})


