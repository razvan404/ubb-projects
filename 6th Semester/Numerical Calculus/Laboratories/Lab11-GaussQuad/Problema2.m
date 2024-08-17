%Problema 2 - Cuadratura Gauss-Radau
syms x;
w=sqrt(1+x) % ponderea initiala
a=-sym(1), b=sym(1)
wb=(b-x)*w
pi2=orto_poly_sym_type('Jacobi',2,sym(1),sym(1)/2)
radacini=solve(pi2==0)'
nodes=[radacini,b]
coefs=gauss_coefs_sym(w,a,b,nodes)

rest_fara_f2=rest_gauss_fara_f(wb,a,b,pi2,3,"Radau")

f=cos(x)
int_gauss_radau=eval(sum(coefs.*subs(f,x,nodes)))

rest_worst=abs(eval(rest_fara_f))
