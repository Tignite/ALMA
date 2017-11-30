#ifndef DATENBANK_H_
#define DATENBANK_H_

#include "Student.h"

typedef struct Datenbank {
public:
	Datenbank();
	Datenbank(int n);
	virtual ~Datenbank();

	void print(int m);
	void sort();

private:
	int n;
	long matnr = 0;
	Student **array;
	long* matnrRegister;
	int* aufsteigendBuffer;
	int* aufsteigendMatnr;
	int* aufsteigendGeb;

	void create();
	bool reg(long matnr);
	void sortMatnr(int s, int n);
	void sortGeb(int s, int n);
}Datenbank;

#endif /* DATENBANK_H_ */
