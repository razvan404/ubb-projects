function [c,val_f,i]=bisection(f,a,b,err,NrMaxIt)
    if nargin < 5, NrMaxIt=100; end
    if nargin < 4, err=1e-12; end

    for i=1:NrMaxIt
        c=(a+b)/2;
        if abs(f(c))<err||abs(a-b)<err||abs(a-b)/abs(c)<err
            val_f=f(c);
            return;
        end
        if f(a)*f(c)<0
            b=c;
        else
            a=c;
        end
    end
end