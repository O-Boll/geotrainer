/*----------------------------------------------------------------------------
This file is part of GeoTrainer.

MIT License

Copyright (c) 2018 Olle Eriksson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
----------------------------------------------------------------------------*/

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
