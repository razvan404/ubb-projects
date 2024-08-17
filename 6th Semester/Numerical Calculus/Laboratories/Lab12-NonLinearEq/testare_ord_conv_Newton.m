syms x a;
f=x^2-a
phi=x-f/diff(f,x,1)
subs(phi,x,sqrt(a))

dphi_1=diff(phi,x,1)
subs(dphi_1,x,sqrt(a))

dphi_2=diff(phi,x,2)
subs(dphi_2,x,sqrt(a))

ord_conv=2
er_asimp=subs(dphi_2,x,sqrt(a))/factorial(sym(2))
