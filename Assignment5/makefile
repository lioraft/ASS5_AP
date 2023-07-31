Ass5: Politician.h DemocratLeader.h DemocratSocial.h RepublicanLeader.h RepublicanSocial.h Party.h RepublicanParty.h DemocratParty.h Error.h PoliticalSys.h Politician.o DemocratLeader.o DemocratSocial.o RepublicanLeader.o RepublicanSocial.o Party.o RepublicanParty.o DemocratParty.o PoliticalSys.o main.o
	g++ Politician.o DemocratLeader.o DemocratSocial.o RepublicanLeader.o RepublicanSocial.o Party.o RepublicanParty.o DemocratParty.o PoliticalSys.o main.o -o Ass5

Politician.o: Politician.h
	g++ -c Politician.cpp

DemocratLeader.o: DemocratLeader.h
	g++ -c DemocratLeader.cpp

DemocratSocial.o: DemocratSocial.h
	g++ -c DemocratSocial.cpp
	
RepublicanLeader.o: RepublicanLeader.h
	g++ -c RepublicanLeader.cpp
	
RepublicanSocial.o: RepublicanSocial.h
	g++ -c RepublicanSocial.cpp

Party.o: Party.h
	g++ -c Party.cpp

RepublicanParty.o: RepublicanParty.h
	g++ -c RepublicanParty.cpp
	
DemocratParty.o: DemocratParty.h
	g++ -c DemocratParty.cpp
	
PoliticalSys.o: PoliticalSys.h
	g++ -c PoliticalSys.cpp
	
main.o: PoliticalSys.h
	g++ -c main.cpp

clean :
	rm -f *.o
