# orangeflower.ls
# (A variation upon PASSIE.LS by C.J.van der Mark jr.)
#
# An l-system to be parsed by Lparser
#
9            # iterations
20           # turn angle
30           # thickness as % of length
#	     # -- rules --
#
# start axiom
#
c(4)FF[>(30)&(90)l]FF[<(120)&(110)r]FF[&(90)l]FF[<(180)&(90)r]S              
#
S='(0.9)F[+(30)FA]F>(30)F[>(135)-(30)FB]FFS
#
A=FC
B=FK
#
C=D
D=E
E=G
G=[^(60)o]
#
K=L
L=M
M=N
N=[^(60)o]
#
# ----------- leaves ---------------------
l=h
r=h
d=Z{[+++e.][++ee.][+eee.][eeee.][-eee.][--ee.][---e.]}
h=[c]ZZZt(3.2)$[++[++ZZd]ZZd][--[--ZZd]ZZd]ZZd
e=t!g
#
# ----------- flowers --------------------
#
o=[&!cj>(90)w>(90)w>(90)w>(90)w>vy>vy>vy>vy>vy>vy>vy>vy>vy>yv>vy>vy>vy>vy>vy>vy>vy>vy]
#
#------------ Spikes in the flower ------
#
v=[ZZc"""""&(90){'''F!!''F!!''F!!''F}]
#
#------------ Flower female stem and male stems
#
w=[[sc??c'!!Ft(-.1)F<<''''!!^^^s]&(100)'(0.5)ZZZ[k][l]]
#
#------------ Colored flower leafs
#
y=[[ZZcccc&(80)'''{-ff+ff|-ff+ff}][ZZccccc&(60)'''{-f+f|-f+f}][ZZcccccc&(35)''''{-f+f|-f+f}]]
j=Z
k=[+d{.].x.}
l=[-h{.].x.}
m=gggm
s=[c^(8)!Ft(-.2)Ft(-.2)Ft(-.2)Fu]
#
#----------------------------------------Pollen holder on male stem
#
u=[???F]
#
#
#F='(1.3)F'(.77)
#f='(1.3)f'(.77)
@
