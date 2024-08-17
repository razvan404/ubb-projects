function [p,i]=Steffensen(g,p0,err,NrMaxIt)
    if nargin < 4, NrMaxIt=100; end
    if nargin < 3, err=1e-10; end

    for i=1:NrMaxIt
        p1=g(p0);
        p2=g(p1);
        p=p0-(p1-p0)^2/(p2-2*p1+p0);
        if abs(p-p0)<err
            return;
        end
        p0=p;
    end
end
