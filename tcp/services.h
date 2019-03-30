#include "database.h"

#ifndef SERVICES_H
#define SERVICES_H

extern char* getProfileByEmail(char profileEmail[]);

extern char* getNamesByCourse(char* course);

extern char* getSkillsByCity(char* city);

extern char* addExpOnProfile(char* email, char* newExp);

extern char* getExpByEmail(char* email);

extern char* getAllInfo();

extern char* getInfosByEmail(char *email);

#endif