

#
# compute SVD  of real matrix
#

#
# create complex  4x4 matrix with normal elements variance 1.0
#
mcxcr A 4 4 1.0

puts {The Matrix A }
vpr $A

#
# compute SVD
# A= uu S vv
#

svd  $A s uu vv 

puts { Singular Values  }

vpr $s


puts {Check  that vv is orthogonal }
puts {Compute vvh= hermitian vv }
herm $vv vvh

mmpy $vv $vvh C

puts {  C= vv vvh Should be Identity Matrix:}

vpr $C 12.4f


puts {Recover A = uu S vvh }

#first create diagonal matrix from s
puts { S =diagonal s }
diag  $s S
vpr $S

herm $uu  uuh

mmpy $S $vv X
mmpy $uu $X  Z

puts { Z = uu S vv Should be A }
vpr $Z 8.2f


puts {The Matrix A }
vpr $A 8.2f

