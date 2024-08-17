nodes=[100 121 81 144];
values=[10 11 9 12];
L=lagrange_sym(nodes,values)
val=double(subs(L,115))
err1=abs(val-sqrt(115))
err2=double(prod(115-nodes)/factorial(sym(4))*subs(abs(diff(sqrt(x),4)),81))


