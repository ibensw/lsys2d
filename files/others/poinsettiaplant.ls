# --- L-System Parser/Mutator --- Lj Lapre ----------------------------------
# L-system which generates a poinsettia plant, with flowers at most apices,
# and sub-apical growth.
# Looks reasonable for recursion depths of 6, 7, 8
# Author: Christina Swindells
6      # recursion depth
18      # angle
12      # thickness as % of length
#
A
#
A=CB>(94)B<(132)a
a=C[p]B<(132)A
B=[&C$Ao]
#
C=c(12)!(.95)~(5)tt(0.05)F
#
F='(1.25)F'(.8)
#
o=[&!c(12)e>w>>>>w>>>>w>>>>w>>>>w]
p=[c(0)ttt~(0.5)l]
e=rF[p]F
r=F[p]Z
w=[c(3)^''''??Z][c(2)&&&&{----'f+f++&&'f+^^''~(0.1)f|----'f+f++&&'f+^^''~(0.1)&f}]
l=[c(12){----f+f++&&'f+^^^'f|----f+f++&&'f+^^^'f}]
@
