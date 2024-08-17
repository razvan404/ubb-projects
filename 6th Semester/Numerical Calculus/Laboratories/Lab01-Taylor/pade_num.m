function R=pade_num(f,m,k,x)
    %R = aproximantul Pade, de ordin [m/k], a lui f calculat in x
    %examplu de apel: syms x; R=pade_num(exp(x),5,6,[-1,1,2])
    %sursa: https://en.wikipedia.org/wiki/Pad%C3%A9_approximant#Computation
    c=sym2poly(taylor(f,'order',m+k+1));
    r0=[1 zeros(1,m+k+1)]; r1=c;
    s0=1; s1=0;
    t0=0; t1=1;
    while length(t1)-1<=k
        aux=r1;
        [q,r1]=deconv(r0,r1);
        r1=polyreduce(r1);
        r0=aux;
        [s0,s1]=update(s0,s1,q);
        [t0,t1]=update(t0,t1,q);
    end
    % coeficientii Pade sunt in r0 si t0
    R=(x.^(length(r0)-1:-1:0)*r0')./(x.^(length(t0)-1:-1:0)*t0');
end

function [s0,s1]=update(s0,s1,q)
    aux=s1;
    produs=conv(q,s1);
    s0=[zeros(1,length(produs)-length(s0)),s0];
    s1=s0-produs;
    s1=polyreduce(s1);
    s0=aux;
end
