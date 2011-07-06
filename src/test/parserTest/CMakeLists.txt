include(${PROJECT_SOURCE_DIR}/script/macro.txt)

find_package(Qt4 REQUIRED)

set(QT_USE_QTTEST TRUE)
include(${QT_USE_FILE})

SET (LIBRARIES pokerRuleSystem ruleSystem)

CREATE_SIMPLE_QT_TEST(parsertest ParserTest)
#CREATE_SIMPLE_QT_TEST(featuretest FeatureTest)
#CREATE_SIMPLE_QT_TEST(functiontest FunctionTest)
