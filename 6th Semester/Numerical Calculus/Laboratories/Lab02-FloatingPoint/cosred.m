function ccos=cosred(x)
    ccos=0;
    u=1;
    n=0;
    while abs(u)
        ccos=ccos+u;
        n=n+1;
        u=-u*x^2/((2*n-1)*(2*n));
    end
end