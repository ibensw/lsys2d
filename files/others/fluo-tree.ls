# --- L-System Parser/Mutator --- Lj Lapre ----------------------------------
11
5
30
#
c(4)'(0.2)FFS                                         # the actual tree
#
S=FFR>(60)R>(60)R>(60)R>(60)R>(60)R>(30)S       # six branches per segment
R=[Ba]                                          # a single branch
#
a=$tF[Cx]Fb                                     # see bop08.ls
b=$tF[Dy]Fa
#
B=&B                                            # angle increments
C=+C
D=-D
#
x=ah                                            # apical elay
y=bh
#
F='(1.25)F'(.8)                                 # elongation rate
#
d=ZFF{[+++e.][++ee.][+eee.][eeee.][-eee.][--ee.][---e.]}
h=cZZZZZt(3.2)$[++[++ZZZZd]ZZZZd][--[--ZZZZd]ZZZZd]ZZZZd
v=Z(60)!(0.90)v
e=t!g
@
