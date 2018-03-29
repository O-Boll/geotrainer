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

#ifndef MESSY_SET_H
#define MESSY_SET_H

#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

template <class T>
class MessySet {

  private:

    std::vector <T> v;
    int index, norep;

    static int urand(int l_bound, int u_bound);

    void shuffle();

  public:

    MessySet();
    void add(const T e);
    void empty();
    int size() const;
    bool isMember(T e) const;
    T pick();
    void remove(T e);
    void setNorep(int n);

};

template <class T>
MessySet<T>::MessySet() {
  index = 0;
  norep = 3;
}

template <class T>
void MessySet<T>::add(T e) {
  if(!isMember(e)) {
    int l = v.size();
    int n = urand(0, l);
    v.insert(v.begin() + n, e);
  }
}

template <class T>
void MessySet<T>::empty() {
  v.clear();
}

template <class T>
int MessySet<T>::size() const {
  return v.size();
}

template <class T>
bool MessySet<T>::isMember(T e) const {
  int l = v.size();
  int n = 0;
  while(n < l) {
    if(v[n] == e) {
      return true;
    }
    n++;
  }
  return false;
}

template <class T>
T MessySet<T>::pick() {
  if(index + 1 > v.size()) {
    shuffle();
    index = 0;
  }
  T e = v[index];
  index++;
  return e;
}

template <class T>
void MessySet<T>::remove(T e) {
  int l = v.size();
  int n = 0;
  while(n < l) {
    if(v[n] == e) {
      v.erase(v.begin() + n);
      break;
    }
    n++;
  }
}

template <class T>
void MessySet<T>::setNorep(int n) {
  norep = n > 0 ? n : 0;
}

template <class T>
int MessySet<T>::urand(int l_bound, int u_bound) {
  static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(l_bound, u_bound);
  return dist(generator);
}

template <class T>
void MessySet<T>::shuffle() {
  reverse(v.begin(),v.end());
  int l = v.size();
  int n = norep;
  while(n + 1 < l) {
    int m = n + urand(0, l - n - 1);
    T temp = v[m];
    v[m] = v[n];
    v[n] = temp;
    n++;
  }
  int k = 0;
  int a_norep = min(norep, l);
  n = a_norep - 1;
  while(n >= 0) {
    int m = a_norep + k + urand(0, l - a_norep);
    v.insert(v.begin() + m, v[n]);
    k++;
    n--;
  }
  v.erase(v.begin(), v.begin() + a_norep);
}

#endif
