# --- L-System Parser/Mutator -- Jelle Ouwerkerk
#
# Inflorescences called racemes
# (single stem, multiple flowers)
#
11     # recursion depth
27.5   # angle
40     # thickness as % of length
W
#
W=<(30)c(4)'(0.2)FF-(3)A
#
A=[<(100)o]FZ<(270)[o]FFA
#
f='(1.25)f'(.8)
F='(1.25)F'(.8)
#
# flower
#
s=Fs
o=[&!c(12)e>w>>>>w>>>>w>>>>w>>>>w]
e=r
r=Z
w=[c(5)^!!!!!F][qc(1){----'f+f++&&'f+^^''f|----'f+f++&&'f+^^''f}]
q=sq
@
