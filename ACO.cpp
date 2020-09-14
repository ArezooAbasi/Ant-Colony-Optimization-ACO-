#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <new>
#include <iostream>
#include <fstream>
#include <assert.h> 

using namespace std;

#define maxcit 17
#define maxdist 100
#define mtour (maxcit * maxdist)
#define mants 10

#define alpha 1.0
#define beta 5.0 
#define rass 0.5 
#define qval 100
#define maxstour 20
#define maxtime 10000
#define pherin (1.0/maxcit)


struct tcity{
	int x, y;
};

struct tantt{

	int curcit, nextcit, pathindex;
	int tabu[maxcit];
	int path[maxcit];
	double tourLength;
};

tcity cities[maxcit];
tantt ants[mants];

double dist[maxcit][maxcit];

double phero[maxcit][maxcit];

double best = (double)mtour;
int bestIndex;

//==========================================================
void init(){
	int from, to, ant;

	//shahr haro misazim

	for (from = 0; from < maxcit; from++){
		//makane shahrharo betore random tolid mikonim

		cities[from].x = rand() % maxdist;
		cities[from].y = rand() % maxdist;

		for (to = 0; to< maxcit; to++){
			dist[from][to] = 0.0;
			phero[from][to] = pherin;
		}
	}

	//faseleye beyne shahrhara hesab mikonim

	for (from = 0; from < maxcit; from++){
		for (to = 0; to < maxcit; to++){
			if (to != from && dist[from][to] == 0.0){
				int xd = pow(abs(cities[from].x - cities[to].x), 2);
				int yd = pow(abs(cities[from].y - cities[to].y), 2);

				dist[from][to] = sqrt(xd + yd);
				dist[to][from] = dist[from][to];

			}
		}
	}

	//morchehara tarif mikonim

	to = 0;
	for (ant = 0; ant < mants; ant++){
		if (to == maxcit)
			to = 0;

		ants[ant].curcit = to++;

		for (from = 0; from < maxcit; from++){
		
			ants[ant].tabu[from] = 0;
			ants[ant].path[from] = -1;
		}

		ants[ant].pathindex = 1;
		ants[ant].path[0] = ants[ant].curcit;
		ants[ant].nextcit = -1;
		ants[ant].tourLength = 0;

		//avalin shahr ra baraye morche entekhab mikonim

		ants[ant].tabu[ants[ant].curcit] = 1;

	}
}
//==========================================================
//pakhsh va tarife morchehara dobare taghri midim
void restartant(){
	int ant, i, to = 0;

	for (ant = 0; ant< mants; ant++){
		if (ants[ant].tourLength < best){
			best = ants[ant].tourLength;
			bestIndex = ant;
		}

		ants[ant].nextcit = -1;
		ants[ant].tourLength = 0.0;

		for (i = 0; i< maxcit; i++){
			ants[ant].tabu[i] = 0;
			ants[ant].path[i] = -1;
		}

		if (to == maxcit)
			to = 0;

		ants[ant].curcit = to++;

		ants[ant].pathindex = 1;
		ants[ant].path[0] = ants[ant].curcit;

		ants[ant].tabu[ants[ant].curcit] = 1;
	}
}
//==========================================================
double prodant(int from, int to){
	return((pow(phero[from][to], alpha) * pow((1.0 / dist[from][to]), beta)));
}
//==========================================================
int snextcit(int ant){
	int from, to;
	double denom = 0.0;

	from = ants[ant].curcit;

	for (to = 0; to<maxcit; to++){
		if (ants[ant].tabu[to] == 0){
			denom += prodant(from, to); 
		}
	}
	assert(denom != 0.0);
	do{
		double p;  
		to++;     
		if (to >= maxcit)
			to = 0;
		if (ants[ant].tabu[to] == 0){
			p = prodant(from, to) / denom;
			double x = ((double)rand() / RAND_MAX);
			if (x < p){
				break;
			}
		}
	} while (1);

	return to;
}
//==========================================================
int simuant(){
	int k;
	int moving = 0;

	for (k = 0; k< mants; k++){
		//check mikone aya shahri baghi monde ya na

		if (ants[k].pathindex < maxcit){
			ants[k].nextcit = snextcit(k);         
			ants[k].tabu[ants[k].nextcit] = 1;         
			ants[k].path[ants[k].pathindex++] = ants[k].nextcit;  
			ants[k].tourLength += dist[ants[k].curcit][ants[k].nextcit];                    

			//mibine be akharin reside ya na age reside dige mire khoneye avalesh

			if (ants[k].pathindex == maxcit){
				ants[k].tourLength += dist[ants[k].path[maxcit - 1]][ants[k].path[0]];
			}

			ants[k].curcit = ants[k].nextcit;
			moving++;

		}
	}

	return moving;
}

//up kardane masir haye piyade ravi

void upmasir(){
	int from, to, i, ant;
	//bara phormonha va tabkhire phormona

	for (from = 0; from < maxcit; from++){
		for (to = 0; to<maxcit; to++){
			if (from != to){
				phero[from][to] *= (1.0 - rass);

				if (phero[from][to]<0.0){
					phero[from][to] = pherin;
				}
			}
		}
	}

	//meghdare phormone jadid be masir ezafe mikone

	for (ant = 0; ant< mants; ant++){
		for (i = 0; i<maxcit; i++){
			if (i < maxcit - 1){
				from = ants[ant].path[i];
				to = ants[ant].path[i + 1];
			}
			else{
				from = ants[ant].path[i];
				to = ants[ant].path[0];
			}

			phero[from][to] += (qval / ants[ant].tourLength);
			phero[to][from] = phero[from][to];

		}
	}

	for (from = 0; from < maxcit; from++){
		for (to = 0; to<maxcit; to++){
			phero[from][to] *= rass;
		}
	}

}
//==========================================================
int main(){
	int curTime = 0;
	srand(time(NULL));

	init();

	while (curTime++ < maxtime){
		if (simuant() == 0){
			upmasir();

			if (curTime != maxtime)
				restartant();

			//cout << "Time is " << curTime << "  --->  " << best << endl;
			cout << "Best tour = " << best << endl;

		}
	}

	cout << "Best result = " << best << endl;


	return 0;
}