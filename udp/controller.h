#ifndef CONTROLLER_H
#define CONTROLLER_H

// Parses given request of query "request_prefix request_type", in which request_prefix
// may be "All" or the id of a single discipline
extern char* getRequest(char request[]);

// Returns list of possible commands
extern char* getCommands();

#endif