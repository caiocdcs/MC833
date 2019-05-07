#include <stdio.h>
#include <stdlib.h>

#include "services.h"
#include "database.h"

int main() {

	char *course = "Computer Scientist";
	char *city = "Sacramento";
	char *email = "sean_parkins@gmail.com";
	char *exp = "Violin";

	char *buffer;
	int size = 0;
	FILE* file = fopen("images/janedoe.jpg", "rb");
	if (!file) {
		perror("error opening file");
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file) + 1;
	fseek(file, 0, SEEK_SET);

	//Allocate memory
    buffer=(char *)malloc(size);
    if (!buffer)
    {
        fprintf(stderr, "Memory error!");
		fclose(file);
        return 1;
	}

    fread(buffer,size,sizeof(char),file);
    fclose(file);

    int i=0;
    while (i < size){
       printf("%02X ",((char)buffer[i]));
       i++;
       if( ! (i % 16) ) printf( "\n" );
    }

	FILE* file1 = fopen("images/teste.jpg", "wb");
	fwrite(buffer, size, sizeof(char), file1);

	fclose(file1);

	// profile *profileReturned = getProfileByEmail(email);
	// printf("%s\n", profileReturned->name);

	// char* test1 = getNamesByCourse(course);
	// char* test2 = getSkillsByCity(city);
	//char* test3 = addExpOnProfile(email, exp);
	//char* test4 = getExpByEmail(email);
	// char* test5 = getAllInfo();
	// char* test6 = getInfosByEmail(email);

	// printf("%s\n", test1);
	// printf("%s\n", test2);
	//printf("%s\n", test3);
	//printf("%s\n", test4);
	// printf("%s\n", test5);
	// printf("%s\n", test6);

	return 0;
}