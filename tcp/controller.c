#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "controller.h"
#include "services.h"
#include "database.h"

#define MAX_CLIENTS 30

typedef struct Request {
    char* prefix;
    char* query;
    char* data;
} Request;

char* requestMessage(char message[]) {
	char *req = malloc(strlen(message) * sizeof(char));
	strcpy(req, message);

	return req;
}

// Gets the request param
Request getRequestParams(char request[]) {
    Request result;
    char* req = malloc(strlen(request) * sizeof(char));
	strcpy(req, request);
	result.prefix = strsep(&req , " ");
	result.query = strsep(&req, " ");
	result.data = strsep(&req, "\n");

    if (result.prefix != NULL && result.prefix[strlen(result.prefix) -1] == '\n') {
        result.prefix[strlen(result.prefix) -1] = '\0';
    }

	if (result.query != NULL &&  result.query[strlen(result.query) -1] == '\n') {
        result.query[strlen(result.query) -1] = '\0';
	}

	return result;
}


// Parses given request of query "request_prefix request_param", in which request_prefix
// maybe an option from the menu
char* getRequest(char request[]) {
	Request request_params;
	char *request_answer;

    request_params = getRequestParams(request);
    if (strcmp(request_params.prefix, "course") == 0) {
        request_answer = getNamesByCourse(request_params.query);
    } else if (strcmp(request_params.prefix, "skill") == 0) {
        request_answer = getSkillsByCity(request_params.query);
    } else if (strcmp(request_params.prefix, "add_experience") == 0) {
        request_answer = requestMessage(addExpOnProfile(request_params.query, request_params.data));
    } else if (strcmp(request_params.prefix, "get_experience")  == 0) {
        request_answer = getExpByEmail(request_params.query);
    } else if (strcmp(request_params.prefix, "all_profiles") == 0) {
        request_answer = getAllInfo();
    } else if (strcmp(request_params.prefix, "profile") == 0) {
        request_answer = getProfileByEmail(request_params.query);
    } else {
        request_answer = requestMessage("Invalid request query.\n\n");
    }

	/* WARNING: It is important that request_answer is freed (in the function caller)
	 * after it is not used anymore */
	return request_answer;
	
}

// Returns possible commands for given socket
char* getCommands() {
	// Instantiating message to return
	char commands_message[] = "\nHere are the commands the server can interpret:\n\
\"course {course}\"\n\
\"skill {city}\"\n\
\"add experience {email} '{experience}'\"\n\
\"get_experience {email}\"\n\
\"all_profiles\"\n\
\"profiles {email}\"\n\n";

	char *commands = malloc(strlen(commands_message) * sizeof(char));
	strcpy(commands, commands_message);

	return commands;
}