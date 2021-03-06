## Aim
The aim is to find all tuples of homotopy equivalent positively curved Eschenburg spaces `E` with bounded invariant `|r|`.  This quest is divided into two tasks:

**Task 1:** Find all positively curved Eschenburg spaces with `|r| ≤ R` for some given bound `R`.  
**Task 2:** Given a list of all such spaces, find all tuples on this list whose homotopy invariants agree.

The implementation of Task 1 is described in detail below.  Task 2 is fairly straight-forward.


## Implementation of Task 1
The task is to find all positively curved Eschenburg spaces `E` with `|r| ≤ R`, for some given positive bound `R`.
  
Lemma 1.4 of [\[CEZ07\]](../README.md#references) shows that all positively curved Eschenburg spaces can be parametrized by quadruples `(k₁, k₂, l₁, l₂)` with

       k₁ ≥ k₂ > l₁ ≥ l₂ ≥ 0                              (1)

Moreover, these quadruples are required to satisfy a list of coprimacy conditions 

      [CEZ07 (1.1)]                                       (2)

which we will spell out below. (The conditions of [\[CEZ07 (1.2)\]](../README.md#references) for positive curvature are automatically satisfied in this parametrization.)  The task is thus to find all quadruples satisfying (1), (2) and

      |r| ≤ R                                             (3)

for some given upper bound `R`.  By [\[CEZ07, proof of Prop. 1.7\]](../README.md#references), such an upper bound implies `R ≥ k₁`. 
So there is a straight-forward way of finding all such quadruples: 
simply iterate over all possible values of `k₁`, `k₂ `, `l₁` and `l₂` between `0`and `R`and check the conditions in each case. 
The problem with this approach is that it is very inefficient (i.e. very slow). 
We therefore use a slightly refined strategy, outlined below. 

### The algorithm
Instead of iterating over quadruples (`k₁`,`k₂`,`l₁`,`l₂`), the algorithm iterates over quadruples (`d`,`n`,`k₁`,`k₂`), where

    n := k₂-l₁
    d := k₁-l₂

In terms of these quadrauples, conditions (1) are above are equivalent to the following conditions: 

    d ≥ n > 0                                             (1'a)
    k₁ ≥ d                                                (1'b)
    k₁ ≥ k₂ ≥ k₁+n-d                                      (1'c)

(The condition `d ≥ n` is in fact superfluous, but it will be useful to know that it holds.) 
The additional conditions [\[CEZ07 (1.1)\]](../README.md#references) that the quadruples (`d`,`n`, `k₁`, `k₂`) need to satisfy are: 

    (n,  d)    coprime                                    (2'a)
    (k₁, n)    coprime                                    (2'b)
    (k₂, d)    coprime                                    (2'c)
    (k₂,    k₁-l₁)  (= (k₂, k₁+n))   coprime             \
    (k₁,    k₂-l₂)  (= (k₁, k₂+d))   coprime              (2'd)
    (k₁-l₁, k₂-l₂)  (= (k₁-k₂+n,k₂-k₁+d))   coprime      /


In terms of `n` and `d`, the formula for `|r|` can be written as: 

    |r| = k₁d + nd + nk₂

Thus, condition (3) is equivalent to: 

    R ≥ k₁d + nd + nk₂                                     (3')

As `k₁ ≥ d` and `k₂ ≥ n ≥ 1`, this implies in particular that:

    R ≥ d² + d + 1                                         (3'a)
    R ≥ k₁d + nd + n²                                      (3'b)
    
##### Step (a):  Find all coprime pairs `(n,d)` with `D ≥ d ≥ n > 0`, where `D := sqrt(R-3/4) - 1/2`
We employ the [standard algorithm for generating Farey sequences](https://en.wikipedia.org/wiki/Farey_sequence#Next_term) to find these. 
(The pairs are interpreted as reduced fractions `0 < n/d ≤ 1`. 
This explains our choice of letters: `n` for numerator and `d` for denominator.) 
The value of the upper bound `D` follows from (3'a). 

##### Step (b):  Find all `k₁` such that `(k₁,n)` coprime with `K₁ ≥ k₁ ≥ d`, where `K₁ := (R-n²)/d - n`. 
The value of `K₁` follows from (3'b).  To find all these `k₁`, proceed in two substeps: 

(b.1) First, search only in the range `d+n > k₁ ≥ d`. 
      We can of course make use of the upper bound, so really we search in the range `min(d+n-1, K₁) ≥ k₁ ≥ d`. 
    
(b.2) All remaining `k₁` with `(k₁,n)` coprime will be of the form `k₁ = k₁' + in` for some positive integer `i`,
      where `k₁'` is one of the values found in (b.1).


##### Step (c):  Find all  `k₂` such that `(k₂, d)` coprime such that `k₁ ≥ k₂ ≥ k₁+n-d` and such that (3') is satisfied.
Condition (3') is equivalent to `(R-k₁d)/n - d ≥ k₂`.  So the range we need to search in is `K₂ ≥ k₂ ≥ k₁+n-d` with
 
    K₂ := min((R-k₁d)/n - d, k₁).
   
Again, to find these `k₂`, we proceed in two substeps:

(c.1) First, search only in the range `k₁+n > k₂ ≥ k₁+n-d`.
      Again, we should also take into account our upper bound, so the actual search will be in the range
      `min(k₁+n-1, K₂) ≥ k₂ ≥ k₁+n-d`.

(c.2) All remaining `k₂` with `(k₂,d)` coprime will be of the form `k₂ = k₂' + id` for some positive integer `i`, 
      where `k₂'`is one of the values found in (c.1).

##### Step (d):  Check the remaining conditions (2'd).

To save memory, in the actual algorithm the steps are interlaced -- as soon as we've found a Farey pair `(n,d)`, we look for a possible value of `k₁`, as soon as we've found that value, we look for `k₂`, etc. until we run out of possibilities;  then we proceed to the next Farey pair.