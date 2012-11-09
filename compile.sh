mkdir build
cd build
cmake ..
make

# Commented out: TS files are updated automatically?
#cd src/lib/pokerRuleSystem/CMakeFiles
#lupdate-qt4 pokerRuleSystem_nl_BE_lupdate.pro -ts pokerRuleSystem_nl_BE.ts
#mv pokerRuleSystem_nl_BE.ts ../../../../../translation/pokerRuleSystem_nl_BE.ts

#cd ../../../../../build

#cd src/lib/ruleSystem/CMakeFiles
#lupdate-qt4 ruleSystem_nl_BE_lupdate.pro -ts ruleSystem_nl_BE.ts
#mv ruleSystem_nl_BE.ts ../../../../../translation/ruleSystem_nl_BE.ts
