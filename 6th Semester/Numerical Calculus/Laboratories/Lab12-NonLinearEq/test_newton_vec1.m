f=@(x) x^6+x^2-1;
df=@(x) 6*x^5+2*x;
x=Newton(f,df,1)
y=x^3

syms x y;
F=[x^2+y^2-1; x^3-y];
J=jacobian(F);
Fh=matlabFunction(F);
Jh=matlabFunction(J);
f=@(X) Fh(X(1),X(2));
df=@(X) Jh(X(1),X(2));
x_y=Newton(f,df,[1;1])
f_x_y =f(x_y)

fsolve(f,[1;1])
