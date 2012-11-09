# dit start the ruleCreat r client op in het Nederlands
#
# runs the client in NL (dutch),
# see runclient_EN.sh for the english version

cp translation/*.qm build/bin/
cd build/bin
./ruleCreator
