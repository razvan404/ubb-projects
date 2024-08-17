f=@(x) sin(1-x.^2);
I0=gauss_quad_num('Jacobi',f,1,aa=-2/3,aa=-1/3);
I1=gauss_quad_num('Jacobi',f,2,aa=-2/3,bb=-1/3);
n=2;
while abs(I0-I1)>=1e-10
  I0=I1;
  n++;
  I1=gauss_quad_num('Jacobi',f,n,aa=-2/3,bb=-1/3);
end
nr_noduri_Gauss_Jacobi=n
Gauss_Jacobi=I1

w=@(x) (1-x).^(-2/3).*(1+x).^(-1/3);
fw=@(x) f(x).*w(x);
cuad_cu_quad=quad(fw,-1,1)

error_Gauss_Jacobi=abs(Gauss_Jacobi-cuad_cu_quad)


f=@(x) exp(-x).*sin(x);
I0=gauss_quad_num('Laguerre',f,1,aa=0);
I1=gauss_quad_num('Laguerre',f,2,aa=0);
n=2;
while abs(I0-I1)>=1e-10
  I0=I1;
  n++;
  I1=gauss_quad_num('Laguerre',f,n,aa=0);
end
nr_noduri=n
Gauss_Laguerre=I1

w=@(x) exp(-x);
fw=@(x) f(x).*w(x);
cuad__cu__quad=quad(fw,0,Inf)

error_Laguerre=abs(Gauss_Laguerre-cuad__cu__quad)


f=@(x) cos(x);
I0=gauss_quad_num('Hermite',f,1);
I1=gauss_quad_num('Hermite',f,2);
n=2;
while abs(I0-I1)>=1e-10
  I0=I1;
  n++;
  I1=gauss_quad_num('Hermite',f,n);
end
nr_noduri=n
Gauss_Hermite=I1

w=@(x) exp(-x.^2);
fw=@(x) f(x).*w(x);
cuad__cu__quad=quad(fw,-Inf,Inf)

error_Hermite=abs(Gauss_Hermite-cuad__cu__quad)