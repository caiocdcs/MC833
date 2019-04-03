#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "controller.h"
#include "services.h"
#include "database.h"

#define MAX_CLIENTS 30

typedef struct Request {
    char prefix;
    char* query;
    char* data;
} Request;

char* requestMessage(char message[]) {
	char *req = malloc(strlen(message) * sizeof(char));
	strcpy(req, message);

	return req;
}

Request getRequestParams(char request[]) {
	Request result;

	char* req = malloc(strlen(request) * sizeof(char));
	strcpy(req, request);

	result.prefix = request[0];

    char* params;
    strsep(&request , "-");
    params = strsep(&request, "-");
    if (params != NULL && params[strlen(params) -1] == '\n') {
        params[strlen(params) -1] = '\0';
    }

	if (result.prefix == '3') {
		result.query = strsep(&params, " ");
		result.data = strsep(&params, "\0");
	} else {
        result.query = strsep(&params, "\0");
	}

	return result;
}


// Parses given request of query "request_prefix request_param", in which request_prefix
// maybe an option from the menu
char* getRequest(char request[]) {
	Request request_params;
	char *request_answer;

    request_params = getRequestParams(request);
	if ((request_params.prefix != '5' && request_params.prefix != '7') && request_params.query == NULL) {
		return requestMessage("Invalid request query.\n");
	}

    if (request_params.prefix == '1') {
        request_answer = getNamesByCourse(request_params.query);
    } else if (request_params.prefix == '2') {
        request_answer = getSkillsByCity(request_params.query);
    } else if (request_params.prefix == '3') {
		if (request_params.data == NULL) {
			return requestMessage("Invalid request query.\n");
		}
        request_answer = requestMessage(addExpOnProfile(request_params.query, request_params.data));
    } else if (request_params.prefix == '4') {
        request_answer = getExpByEmail(request_params.query);
    } else if (request_params.prefix == '5') {
        request_answer = getAllInfo();
    } else if (request_params.prefix == '6') {
        request_answer = getInfosByEmail(request_params.query);
    } else if (request_params.prefix == '7') {
        request_answer = getCommands();
    } else {
        request_answer = requestMessage("Invalid request query.\n");
    }

	/* WARNING: It is important that request_answer is freed (in the function caller)
	 * after it is not used anymore */
	return request_answer;
}

// Returns possible commands for given socket
char* getCommands() {
	// Instantiating message to return
	char commands_message[] = 
	"\nHere are the commands to use the server properly:\n\
	\"1-{course}\"\n\
	\"2-{city}\"\n\
	\"3-{email} {experience}\"\n\
	\"4-{email}\"\n\
	\"5\"\n\
	\"6-{email}\"\n\
	\"7\"\n\n";

	char *commands = malloc(strlen(commands_message) * sizeof(char));
	strcpy(commands, commands_message);

	return commands;
}