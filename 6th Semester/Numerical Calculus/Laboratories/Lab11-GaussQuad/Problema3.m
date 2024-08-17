%Problema 2 - Cuadratura Gauss-Radau
syms x;
w=exp(-x) % ponderea initiala
a=sym(0), b=sym(Inf)
wa=(x-a)*w
pi2=orto_poly_sym_type('Laguerre',2,sym(1))
radacini=solve(pi2==0)'
nodes=[a,radacini]
coefs=gauss_coefs_sym(w,a,b,nodes)

rest_fara_f=rest_gauss_fara_f(wa,a,b,pi2,3,"Radau")

f=log(1+exp(-x))*exp(x)
int_gauss_radau=eval(sum(coefs.*subs(f,x,nodes)))

df5=diff(f,x,5)

disp("df5 depinde doar de e^x, unde x este intre 0 si Inf")
disp("facem schimbarea de variabila e^x=1/y <=> x=log(1/y) => y este intre 0 si 1")
syms y;
fplot(matlabFunction(subs(df5,x,log(1/y))),[0,1])
disp("se observa pe grafic ca functia este intre -0.1 si 0.1")

rest_worst=abs(eval(rest_fara_f))*0.1
