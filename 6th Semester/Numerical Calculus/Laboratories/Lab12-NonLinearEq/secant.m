function [x2,val_f,i]=secant(f,x0,x1,err,NrMaxIt)
    if nargin < 5, NrMaxIt=100; end
    if nargin < 4, err=1e-12; end

    for i=1:NrMaxIt
        x2=(x0*f(x1)-x1*f(x0))/(f(x1)-f(x0));
        if abs(f(x2))<err||abs(x2-x1)<err||abs(x2-x1)/abs(x2)<err
            val_f=f(x2);
            return;
        end
        x0=x1;
        x1=x2;
    end
end