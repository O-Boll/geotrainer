#ifndef STRFCNS_H
#define STRFCNS_H

#include <string>

namespace strfcns {

std::string itos(int n);

int stoi(std::string s);

void str_cpy(char* &c0, const char* c1);

}

#endif
