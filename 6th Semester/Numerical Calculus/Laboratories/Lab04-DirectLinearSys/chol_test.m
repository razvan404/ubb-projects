B=rand(10,10)
det(B)
A=B'*B
b=A*ones(10,1)
x=sol_sys_chol(A,b)
%norm(A*x-b)
