#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "services.h"
#include "database.h"

#define TAM 6

#define expTAM 50

extern profile profiles[TAM];

profile* getProfileByEmail(char profileEmail[]) {

	int i;
	int profile_qty = sizeof(profiles)/sizeof(profile);
	profile *profileToReturn;

	for (i = 0; i < profile_qty; i++) {
		if (strcmp(profiles[i].email, profileEmail) == 0) {
			return &profiles[i];
		}
	}

	return NULL;
}

char* getNamesByCourse(char* course) {

	int i;
	char *namesList;

	namesList = malloc(sizeof(char));

	for(i = 0; i < TAM; i++) {
		if (strcmp(profiles[i].course, course) == 0) {
			namesList = realloc(namesList, (strlen(namesList) + strlen(profiles[i].name) + 1) * sizeof(char));
			strcat(namesList, profiles[i].name);
			strcat(namesList, "\n");
		}
	}

	strcat(namesList, "\0");

	return namesList;
}


char* getSkillsByCity(char* city) {

	int i;
	char *skillsList;

	skillsList = malloc(sizeof(char));

	for(i = 0; i < TAM; i++) {
		if (strcmp(profiles[i].city, city) == 0) {
			skillsList = realloc(skillsList, (strlen(skillsList) + strlen(profiles[i].skill) + 1) * sizeof(char));
			strcat(skillsList, profiles[i].skill);
			strcat(skillsList, "\n");
		}
	}

	strcat(skillsList, "\0");

	return skillsList;
}

char* addExpOnProfile(char* email, char newExp[expTAM]) {
	
	profile *profileReturned = getProfileByEmail(email);
	int expLenght;

	if (profileReturned == NULL) {
		 return "ERROR\n";
	}

	for(expLenght = 0; profileReturned->exp[expLenght] != NULL; expLenght++) {}

	profileReturned->exp[expLenght] = malloc(expTAM * sizeof(char));
    strcpy(profileReturned->exp[expLenght], newExp);

	return "SUCCESS\n";

}

char* getExpByEmail(char* email) {

	int i, y;
	char *expList = malloc(sizeof(char));

	for(i = 0; i < TAM; i++) {
		if (strcmp(profiles[i].email, email) == 0) {
			for(y = 0; profiles[i].exp[y] != NULL; y++) {
				expList = realloc(expList, (strlen(expList) + strlen(profiles[i].exp[y]) + 2) * sizeof(char));
				strcat(expList, profiles[i].exp[y]);
				strcat(expList, ", ");
			}
			break;
		}
	}

	strcat(expList, "\0");

	return expList;
}

char* getAllInfo() {

	int i, y;
	char *info;

	info = malloc(sizeof(char));

	for(i = 0; i < TAM; i++) {
	
		info = realloc(info, (strlen(info) + strlen(profiles[i].email) + strlen(profiles[i].name) + strlen(profiles[i].city) + strlen(profiles[i].course) + strlen(profiles[i].skill) + strlen(profiles[i].photoUrl) + strlen(profiles[i].exp) + 12) * sizeof(char));
		strcat(info, profiles[i].email);
		strcat(info, ", ");
		strcat(info, profiles[i].name);
		strcat(info, ", ");
		strcat(info, profiles[i].city);
		strcat(info, ", ");
		strcat(info, profiles[i].course);
		strcat(info, ", ");
		strcat(info, profiles[i].skill);
		strcat(info, ", ");
        strcat(info, profiles[i].photoUrl);
        strcat(info, ", ");

		for(y = 0; profiles[i].exp[y] != NULL; y++) {
			info = realloc(info, (strlen(info) + strlen(profiles[i].exp[y]) + 2) * sizeof(char));
			strcat(info, profiles[i].exp[y]);
			strcat(info, "\n");
		}
	}

	return info;
}

char* getInfosByEmail(char *email) {

	int i, y;
	char *info;

	info = malloc(sizeof(char));

	for(i = 0; i < TAM; i++) {

		if (strcmp(profiles[i].email, email) == 0) {
			info = realloc(info, (strlen(info) + strlen(profiles[i].email) + strlen(profiles[i].name) + strlen(profiles[i].city) + strlen(profiles[i].course) + strlen(profiles[i].skill) + strlen(profiles[i].photoUrl) + strlen(profiles[i].exp) + 12) * sizeof(char));
			strcat(info, profiles[i].email);
			strcat(info, ", ");
			strcat(info, profiles[i].name);
			strcat(info, ", ");
			strcat(info, profiles[i].city);
			strcat(info, ", ");
			strcat(info, profiles[i].course);
			strcat(info, ", ");
			strcat(info, profiles[i].skill);
            strcat(info, ", ");
            strcat(info, profiles[i].photoUrl);
            strcat(info, ", ");
			
			for(y = 0; profiles[i].exp[y] != NULL; y++) {
                info = realloc(info, (strlen(info) + strlen(profiles[i].exp[y]) + 2) * sizeof(char));
                strcat(info, profiles[i].exp[y]);
                strcat(info, ", ");
            }

			break;
		}
	}

	strcat(info, "\0");

	return info;
}
