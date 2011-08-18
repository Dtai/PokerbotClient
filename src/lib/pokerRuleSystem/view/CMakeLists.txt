include(${PROJECT_SOURCE_DIR}/script/macro.txt)

set (SOURCES
	editbooldialog.cpp
	editnumericaldialog.cpp
	editcardlistdialog.cpp
	cardeditwidget.cpp
	validcombobox.cpp
	cardEvaluator.cpp
	cardEvaluatorCreator.cpp
)
set (HEADERS
	editbooldialog.hpp
	editnumericaldialog.hpp
	editcardlistdialog.hpp
	cardeditwidget.hpp
	validcombobox.hpp
	cardEvaluator.hpp
	cardEvaluatorCreator.cpp
)

set (Q_MOC_HPP
	editbooldialog.hpp
	editnumericaldialog.hpp
	editcardlistdialog.hpp
	cardeditwidget.hpp
	validcombobox.hpp
	cardEvaluator.hpp
)
set (Q_UI
	editconstantdialog.ui
	editcardlistdialog.ui
	cardeditwidget.ui
	cardEvaluator.ui
)
set (Q_RES )
set (SUBDIRECTORIES )

#INCLUDE_ALL_QT_SUBDIRECTORIES_HEADER_SOURCES(${SUBDIRECTORIES})


