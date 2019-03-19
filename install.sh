g++ Ocean_nms_DB.cpp Application_Main.cpp Ocean_nms_snmp.cpp devcollector_msg.pb.cc  msg_common.pb.cc -lPocoFoundation  -lPocoUtil  -lPocoData -lPocoDataMySQL -lPocoJSON  -lsnmp++  -lprotobuf -std=c++11 -Wall -o App
#g++ Ocean_nms_snmp_test.cpp -lsnmp++  -lprotobuf  -std=c++11 -o abcd
