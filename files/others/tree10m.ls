# --- L-System Parser/Mutator --- Lj Lapre ----------------------------------
# Modification of tree10.ls by Christina Swindells
# - initial production axiom changed to simplify tree growth
# - leaves sparser and farther from the actual branches so that branching
#	is more visible
# - depth of recursion decreased, width:length ratio and base angle also
#	tweaked
8
30
12
#
c(12)A
#
A=CB>(94)B<(132)B
B=[&C$AL]
#
C=!(.95)~(5)t(0.05)F
#
F='(1.25)F'(.8)
#
L=[~f(200)c(8){+(30)f(200)-(120)f(200)-(120)f(200)}]
f=z
z=_
@
