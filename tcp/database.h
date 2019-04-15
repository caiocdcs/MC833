#ifndef DATABASE_H
#define DATABASE_H

#define expTAM 50

typedef struct profile {
	char* email;
	char* name;
	char* photoUrl;
	char* city;
	char* course;
	char* skill;
	char* exp[expTAM];
} profile;

extern profile profiles[];

#endif