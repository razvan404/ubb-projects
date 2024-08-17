f=@(x) x-cos(x)
g=@(x) cos(x)

clf; hold  on;
plot([0 pi/2],[0 0])
fplot(f,[0,pi/2])

c0=fzero(f,pi/2)
[c1,fc,nr_it]=bisection(f,0,pi/2)
[c2,fc,nr_it]=false_pos(f,0,pi/2)
[x2,val_f,i]=secant(f,0,pi/2)
[p,i]=Steffensen(g,pi/4)
df=@(x) 1+sin(x)
[x1,val_f,i]=Newton(f,df,pi/4,1e-12,100)
[x1,i]=succesiv(g,pi/4)
phi=@(x) x-f(x)./df(x)
[x1,i]=succesiv(phi,pi/4)

