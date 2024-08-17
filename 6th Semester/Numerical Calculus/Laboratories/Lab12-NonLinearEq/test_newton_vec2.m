syms x y z;
F=[9*x^2+36*y^2+4*z^2-36;
  x^2-2*y^2-20*z;
  x^2-y^2+z^2];
J=jacobian(F);
Fh=function_handle(F);
Jh=function_handle(J);
f=@(X) Fh(X(1),X(2),X(3)); 
df=@(X) Jh(X(1),X(2),X(3));

sol=Newton(f,df,[1;1;0])
err=norm(f(sol),Inf)
fsolve(f,[1;1;0])

sol=Newton(f,df,[-1;1;0])
err=norm(f(sol),Inf)
fsolve(f,[-1;1;0])

sol=Newton(f,df,[1;-1;0])
err=norm(f(sol),Inf)
fsolve(f,[1;-1;0])

sol=Newton(f,df,[-1;-1;0])
err=norm(f(sol),Inf)
fsolve(f,[-1;-1;0])
