function res=pnorm(A,p)
    n=length(A);
    res=0;
    if p==1
        res=max(sum(abs(A), 1));
    elseif p==2
        res=sqrt(max(eig(A'*A)));
    elseif p==inf
        res=max(sum(abs(A), 2));
    end
end

