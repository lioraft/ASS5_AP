#include "PoliticalSys.h"

int main(int argc, char* argv[]) {
    string filename;
    filename = argv[1];
    PoliticalSys* politicalSys = new PoliticalSys(filename);
    char menuOption = '1';
    while(menuOption!='0')
    {
        try {
        cout<< "1. Add Politician" << endl;
        cout<< "2. Add Party" << endl;
        cout<< "3. Remove Politician" << endl;
        cout<< "4. Remove Party" << endl;
        cout<< "5. Elections" << endl;
        cout<< "6. Print Politicians" << endl;
        cout<< "7. Print Parties" << endl;
        cout<< "8. Biggest Party" << endl;
        cout<< "0. Exit" << endl;
        cin >> menuOption;
        switch(menuOption){
            case '1': {
                politicalSys->addPoliticianNoFile();
                break;
            }
            case '2': {
                politicalSys->addPartyNoFile();
                break;
            }
            case '3':
                politicalSys->removePoliticianFromSystem();
                break;
            case '4':
                politicalSys->removePartyFromSystem();
                break;
            case '5':
                politicalSys->elections();
                break;
            case '6':
                politicalSys->printPoliticians();
                break;
            case '7':
                politicalSys->printParties();
                break;
            case '8':
                politicalSys->printBiggestParty();
                break;
            case '0':
                delete politicalSys;
                break;
            default: break;
        }
        }
        catch(Error &err) {
            err.Handle();
        }
    }

    return 0;
}