#include "StrFcns.h"

namespace strfcns {

std::string itos(int n) {
  std::string s;
  if(n == 0) { s.push_back('0'); return s; }
  int o = 0;
  if(n < 0) { s.push_back('-'); n = -n; o = 1; }
  while(n) {
    int d = n % 10;
    n /= 10;
    s.insert(s.begin() + o, char(48 + d));
  }
  return s;
}

int stoi(std::string s) {
  int n = 0, i = 0;
  int sign = 1;
  if(s.size() == 0)
    return 0;
  if(s[0] == '-') {
    sign = -1;
    i++;
  }
  while(s[i] >= '0' && s[i] <= '9') {
    n = 10 * n + s[i] - '0';
    i++;
  }
  return sign * n;
}

void str_cpy(char* &c0, const char* c1) {
  int i = 0, n = 0;
  while(c1[n])
    n++;
  c0 = new char[++n];
  while(i < n)
    c0[i] = c1[i++];
}

}
