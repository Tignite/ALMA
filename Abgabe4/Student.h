#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>		/* string */
#include <iostream>		/* cin, cout */
#include <stdlib.h>     /* srand, rand */

typedef struct Student {
public:
	Student();
	Student(long matnr, short* geb, short studienfach, short fachsemester);
	virtual ~Student();

	void print();
	bool setMatnr(long matnr);
	bool setGeb(short* geb);
	bool setStudienfach(short studienfach);
	bool setFachsemester(short fachsemester);
	long getMatnr();
	std::string getGeb();
	short* getGebShort();
	short getStudienfach();
	short getFachsemester();
	void randMatnr();

private:
	long matnr;
	short geb [3];
	short studienfach;
	short fachsemester;

	int pseudoRand(int limit);
	bool schaltjahr(short n);
	void randGeb();
}Student;

#endif /* STUDENT_H_ */
