# --- L-System Parser/Mutator --- Lj Lapre ----------------------------------
# Created by Christina Swindells to examine the structure of 5-petaled flowers
4      # recursion depth
18      # angle
50      # thickness as % of length
#
c(12)[&&&&&l+++l++++l++++++l]o
#
o=[&!c(12)e>w>>>>w>>>>w>>>>w>>>>w]
e=FF
w=[c(3)^!F][c(5)&&&&{---f+++f|---f+++f}]
l=[c(8){++f--ff--f++|++f--ff--f}]
@
