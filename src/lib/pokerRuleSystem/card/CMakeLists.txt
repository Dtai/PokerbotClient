include(${PROJECT_SOURCE_DIR}/script/macro.txt)

set (SOURCES
	card.cpp
	carddrawer.cpp
	suitparser.cpp
	rankparser.cpp
	cardexpressionvalidator.cpp
)
set (HEADERS
	card.hpp
	carddrawer.hpp
	suitparser.hpp
	rankparser.hpp
	cardexpressionvalidator.hpp
        simpleparser.hpp
)

set (Q_MOC_HPP
	cardexpressionvalidator.hpp
)
set (Q_UI
)
set (Q_RES )
set (SUBDIRECTORIES )

#INCLUDE_ALL_QT_SUBDIRECTORIES_HEADER_SOURCES(${SUBDIRECTORIES})


