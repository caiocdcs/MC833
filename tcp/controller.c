#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "controller.h"
#include "services.h"

#define MAX_CLIENTS 30

char* invalidRequest() {
	char req_answer[] = "Invalid request type.\n\n";
	char *invalid_req = malloc(strlen(req_answer) * sizeof(char));
	strcpy(invalid_req, req_answer);

	return invalid_req;
}

// Gets the request param
char* getRequestParam(char request[]) {

	char *space_pointer;
	char *request_type;

	space_pointer = strstr(request, " ");

	if (space_pointer == NULL) {
		return NULL;
	}

	space_pointer++;
	request_type = malloc(strlen(space_pointer) * sizeof(char));
	strcpy(request_type, space_pointer);

	char *pos;
	pos = strstr(request_type, '\n');

	if (pos != NULL)
	    *pos = '\0';

	return request_type;
}


// Parses given request of type "request_prefix request_param", in which request_prefix
// maybe an option from the menu
char* getRequest(char request[]) {

	char *request_param;
	char *request_answer;

	request_param = getRequestParam(request);

    if (strncmp(request, "course", 6) == 0) {
        request_answer = course(request_param);
    } else if (strncmp(request, "skill", 5)) {
        request_answer = skill(request_param);
    } else if (strncmp(request, "add_experience", 14)) {
        request_answer = add_experience(request_param);
    } else if (strncmp(request, "get_experience", 14)) {
        request_answer = get_experience(request_param);
    } else if (strncmp(request, "all_profiles", 12)) {
        request_answer = all_profiles();
    } else if (strncmp(request, "profile", 7)) {
        request_answer = profile(request_param)
    } else {
        request_answer = invalidRequest();
    }

	free(request_param);

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