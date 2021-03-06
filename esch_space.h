#pragma once
#include "config.h"
#include <array>               // std::array;
#include <boost/rational.hpp>  // boost::rational;

class Space {
 private:
  std::array<INT_P,3> k_;
  std::array<INT_P,3> l_;
  INT_R r_;            // = r(k,l); it can be positive or negative.
                       // (in [CEZ07], "r := |r(k,l)|")
  INT_R s_;            // = s(k,l) modulo |r(k,l)|
  int_least8_t Sigma_; // = -l1-l2-l3 mod 3
  //M2//int_least8_t m2_; // = l1 + l2 + l3 + l1l2 + l1l3 + l2l3 mod 2
  INT_R p1_;           // = p_1(k,l) modulo |r(k,l)|
  boost::rational<INT_KS> s2_;

  // KS-invariants s2 and s22 take values in interval (-1/2,1/2]
  static const boost::rational<INT_KS> KS_UNKNOWN;      // (set to -1/1 in .cpp)
  static const boost::rational<INT_KS> KS_UNCOMPUTABLE; // (set to 1/1 in .cpp)
  // KS-invariants s2, s22 are uncomputable if condition C is not satisfied

  int good_col_or_row;
  static const int GOOD_CoR_UNKNOWN = -1;
  static const int GOOD_CoR_NONEXISTENT = 6;
  // 0,1,2  = col 1,2,3 satisfies condition C
  // 3,4,5  = row 1,2,3 satisfies condition C
  void find_good_col_or_row(void);
  int gcdA(int i, int j, int ii, int jj);
  void compute_s2_from_row(int j);
  void compute_s2_from_col(int j);
  boost::rational<INT_KS> lens_s2(INT_P p, std::array<INT_P,4> param);

public:
  // Constructor:
  Space(std::array<INT_P,3> kkk, std::array<INT_P,3>);

  // Methods that change class members:
  bool test_condition_C(); 
  bool compute_KS_invariants();  // same return value as conditionC, but also computes s22 & s2

  // Getters that don't change class members:
  bool is_space(void) const;
  bool is_positively_curved(void) const;
  const std::array<INT_P,3>& k() const { return k_; }
  const std::array<INT_P,3>& l() const { return k_; }
  const INT_R& r() const { return r_; }
  const INT_R& s() const { return s_; }
  const int_least8_t Sigma() const { return Sigma_; }
  //M2//const int_least8_t m2() const { return m2_; }
  const INT_R& p1() const { return p1_; }
  const boost::rational<INT_KS>& s2() const {return s2_; }
  boost::rational<INT_KS> s22() const;

  // Other methods that don't change class members:
  // (note that wrong values of s2 & s22 will be printed
  //  if they haven't yet been computed)
  void print(FILE* file) const;
  void print(void) const;

  // static methods:
  enum class comp {SMALLER, MAYBE_SMALLER, EQUAL, MAYBE_EQUAL, MAYBE_GREATER, GREATER};  // MAYBE_EQUAL is return when KS-invariants are unknown/uncomputable
  static comp compareHomotopyType(const Space& E1, const Space& E2);
  //M2//static comp compareHomotopyType_using_KS(const Space& E1, const Space& E2);            // legacy
  static comp compareTangentialHomotopyType(const Space& E1, const Space& E2);
  static comp compareHomeomorphismType(const Space& E1, const Space& E2);
};


