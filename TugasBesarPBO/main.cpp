#include <iostream>
#include <string>
#include "Character.h"
#include "Monster.h"
#include "Papan.h"
#include "Relik.h"
//#include <Windows.h>
//#include <time.h>
#include <ctime>
using namespace std;




void f() {
	using namespace std;
	clock_t begin = clock();
	int i;
	cin >> i;
	 while (i--){}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
}
int main()
{

	int holder;
	char holder_c;
	string holder_str;
	Papan *mainframe = new Papan;
	mainframe->ReadMap();
	cout << "Siapa namamu : "; cin >> holder_str;
	mainframe->reggu->setName(holder_str);
	cout << "Oke "<<mainframe->reggu->getName()<<" Mau Lvl brp? A ? B? C?" << endl;
	cin >> holder_c;
	mainframe->setLvl(holder_c);
	clock_t begin = clock();
	clock_t end;
	double elapsed_time;
	while (1) { 
		end = clock();
		elapsed_time = double(end - begin) / CLOCKS_PER_SEC;
		if (elapsed_time-trunc(elapsed_time)>0.5
			&& elapsed_time - trunc(elapsed_time)<0.52) {
			mainframe->musuh[0]->gerakAcak(mainframe->getMap(0));//error di gerak acaknya
			begin = clock(); mainframe->ShowMap();
		}
		
	}

	getchar();
    return 0;
}
