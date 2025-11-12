

#
# compute SVD  of real matrix
#

#
# create complex  4x4 matrix with normal elements variance 1.0
#
mcxcr A 2 4 1.0

puts {The Matrix A }
vpr $A

#
# compute SVD
# A= uu S vv
#

svd  $A s uu vv 

puts { Singular Values  }

vpr $s

puts { V Matrix  }
vpr $vv

puts { U Matrix  }
vpr $uu

puts {Check  that vv is orthogonal }
puts {Compute vvh= hermitian vv }
herm $vv vvh

mmpy $vv $vvh C

puts {  C= vv vvh Should be Identity Matrix:}

vpr $C 12.4f




#first create diagonal matrix from s
#mset $Matrix $value $i $k
#vget $Vector  $i ?value?


puts { S =diagonal s }
mcr S 2 4 
vget $s 0 s0
mset $S $s0 0 0 
vget $s 1 s1
mset $S $s1 1 1
vpr $S

herm $uu  uuh


mmpy $uu $uuh CU

puts {  CU= uu uuh Should be Identity Matrix:}

vpr $CU



puts {Recover A = uu S vvh }
mmpy $S $vv X
mmpy $uu $X  Z

puts { Z = uu S vv Should be A }
vpr $Z 8.2f


puts {The Matrix A }
vpr $A 8.2f

