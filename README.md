## Introduction

* This project implements the Linear Programming (LP) decoding of  Low-Density Parity-Check (LDPC) codes. 
* The model is based on the the following paper. 
J. Feldman, M. J. Wainwright and D. R. Karger, "Using linear programming to Decode Binary linear codes," in IEEE Transactions on Information Theory, vol. 51, no. 3, pp. 954-972, March 2005.
* The solver used here is GLPK (GNU Linear Programming Kit). 
* The txt file describing the codeword should follow the formate described in David Mackay's Website. 
http://www.inference.org.uk/mackay/codes/alist.html


## Usuage

* git clone
* install GLPK 
* prepare your codeword file and modify the variable *codeword_txt* defined in Top_main.c