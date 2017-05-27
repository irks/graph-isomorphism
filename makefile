1T: 
	g++ -Wall -std=c++11 -O1 gIsoOneThread.cpp -o progOneThread 

MT: 
	g++ -Wall -std=c++11 -pthread -O2 gIsoMultiThreading.cpp -o progMultiThreading 
