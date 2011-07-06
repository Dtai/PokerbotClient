include(${PROJECT_SOURCE_DIR}/script/macro.txt)

find_package(Qt4 REQUIRED)

set(QT_USE_QTTEST TRUE)
include(${QT_USE_FILE})

SET (LIBRARIES ruleSystem pokerRuleSystem)

CREATE_SIMPLE_QT_TEST(serializationtest SerializationTest)
