// Copyright (c) 2009 hp-FEM group at the University of Nevada, Reno (UNR).
// Distributed under the terms of the BSD license (see the LICENSE
// file for the exact terms).
// Email: hermes1d@googlegroups.com, home page: http://hpfem.org/

#ifndef __HERMES_COMMON_TUPLE_H
#define __HERMES_COMMON_TUPLE_H

namespace Hermes {

/// A vector of values.
/** This class is used to pass a variable number of parameters in a type-safe fashion.
 *  \par Suggested Use
 *  Let us assume a function foo(const Tuple<Solution*>&) and instances sln1-sln3 of a class Solution. Then,
 *  - 1 parameter: foo(&sln1);
 *  - 2 up to 10 parameters: foo(Tuple<double>(&sln1, &sln2, &sln3));
 *  - more than 10 parameters: Fill the instance similar to STL vector (std::vector). */
template<typename T>
class Tuple {
public:
  /// A default constructor. Creates an empty vector.
  Tuple() { };
  /// 1 parameter constructor.
  Tuple(const T& a) { this->push_back(a); };
  /// 2 parameters constructor.
  Tuple(const T& a, const T& b) { this->reserve(2); this->push_back(a); this->push_back(b); };
  /// 3 parameters constructor.
  Tuple(const T& a, const T& b, const T& c) { this->reserve(3); this->push_back(a); this->push_back(b); this->push_back(c); };
  /// 4 parameters constructor.
  Tuple(const T& a, const T& b, const T& c, const T& d) { this->reserve(4); this->push_back(a); this->push_back(b); this->push_back(c); this->push_back(d); };
  /// 5 parameters constructor.
  Tuple(const T& a, const T& b, const T& c, const T& d, const T& e) { this->reserve(5); this->push_back(a); this->push_back(b); this->push_back(c); this->push_back(d); this->push_back(e); };
  /// 6 parameters constructor.
  Tuple(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f) { this->reserve(6); this->push_back(a); this->push_back(b); this->push_back(c); this->push_back(d); this->push_back(e); this->push_back(f); };
  /// 7 parameters constructor.
  Tuple(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g) { this->reserve(7); this->push_back(a); this->push_back(b); this->push_back(c); this->push_back(d); this->push_back(e); this->push_back(f); this->push_back(g); };
  /// 8 parameters constructor.
  Tuple(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h) { this->reserve(8); this->push_back(a); this->push_back(b); this->push_back(c); this->push_back(d); this->push_back(e); this->push_back(f); this->push_back(g); this->push_back(h); };
  /// 9 parameters constructor.
  Tuple(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i) { this->reserve(9); this->push_back(a); this->push_back(b); this->push_back(c); this->push_back(d); this->push_back(e); this->push_back(f); this->push_back(g); this->push_back(h); this->push_back(i); };
  /// 10 parameters constructor.
  Tuple(const T& a, const T& b, const T& c, const T& d, const T& e, const T& f, const T& g, const T& h, const T& i, const T& j) { this->reserve(10); this->push_back(a); this->push_back(b); this->push_back(c); this->push_back(d); this->push_back(e); this->push_back(f); this->push_back(g); this->push_back(h); this->push_back(i); this->push_back(j); };

  // TODO: Add Tuple<T>::iterator and Tuple<T>::const_iterator embedded classes to complete the support for std iterators.
  // Hints: http://stackoverflow.com/questions/2844339/c-iterator-and-const-iterator-problem-for-own-container-class
  
  typename std::vector<T>::iterator begin() {
      return this->_v.begin();
  }
  typename std::vector<T>::iterator end() {
      return this->_v.end();
  }

  void push_back(const T& x) {
      this->_v.push_back(x);
  }

  T& back() {
      return this->_v.back();
  }

  void reserve(const int size) {
      this->_v.reserve(size);
  }

  void clear() {
      this->_v.clear();
  }

  int size() {
      return this->_v.size();
  }

  T& operator[](const int index) {
      return this->_v[index];
  }

  const T& operator[](const int index) const {
      return this->_v[index];
  }

  T at(const int index) {
      return this->_v.at(index);
  }

  Tuple& operator=(const Tuple &other) {
      this->_v = other._v;
      return *this;
  }

  Tuple& operator=(const std::vector<T> &other) {
      this->_v = other;
      return *this;
  }

  bool operator==(const Tuple &other) const {
      return this->_v == other._v;
  }

  bool operator!=(const Tuple &other) const {
      return this->_v != other._v;
  }

  // Look up an integer number in an array.
  int find_index_slow(const T& x) {
    for (int i=0; i < this->size(); i++) {
      if ((*this)[i] == x)
         return i;
    }
    throw std::runtime_error("Index not found");
  }

  // Returns maximum of the Tuple<T> in case of T == int.
  int max() {
    if (this->size() == 0)
        throw std::runtime_error("Empty Tuple");
    int m;
    if(typeid((*this)[0]) != typeid(m))
      throw std::runtime_error("Tuple<T>::max() called and T != int.");
    m = (int)(*this)[0];
    for (int i=1; i < this->size(); i++)
        if ((int)(*this)[i] > m)
            m = (int)(*this)[i];
    return m;
  }

  // Returns minimum of the Tuple<T> in case of T == int.
  int min() {
    if (this->size() == 0)
        throw std::runtime_error("Empty Tuple");
    int m;
    if(typeid((*this)[0]) != typeid(m))
      throw std::runtime_error("Tuple<T>::max() called and T != int.");
    m = (int)(*this)[0];
    for (int i=1; i < this->size(); i++)
        if ((int)(*this)[i] < m)
            m = (int)(*this)[i];
    return m;
  }

  // Look up an integer number in an array.
  // This prepares a permut array, so subsequent calls are very fast
  int find_index(int x, bool throw_exception=true) {
    if (this->size() == 0) {
      if (throw_exception) {
        throw std::runtime_error("Empty Tuple");
      }
      else return -1;
    }
    int idx;
    if(typeid((*this)[0]) != typeid(idx))
      throw std::runtime_error("Tuple<T>::find_index() called and T != int.");
    
    if (this->_permut.size() == 0) {
        // Initialize the permut array
        this->_min = this->min();
        this->_max = this->max();
        for (int i=0; i < (int)this->_max+1; i++) this->_permut.push_back(-1);
        for (int i=0; i < this->size(); i++) this->_permut[(int)(*this)[i]] = i;
    }
    if (((int)this->_min <= x) && (x <= (int)this->_max))
        idx = this->_permut[x];
    else
        idx = -1;
    if (idx == -1) {
        if (throw_exception) {
            std::ostringstream s;
            s << "Index '" << x << "' not found";
            throw std::runtime_error(s.str());
        }
        else
            return -1;
    }
    return idx;
  }

  void print() {
    printf("[");
    for (int i=0; i < this->size(); i++) printf("%d ", (*this)[i]);
    printf("]\n");
  }

  private:
    std::vector<T> _v;
    std::vector<int> _permut;
    int _min, _max;
};

} // namespace Hermes

#endif
