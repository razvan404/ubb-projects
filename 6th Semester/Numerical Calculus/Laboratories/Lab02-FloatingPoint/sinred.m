function ssin=sinred(x)
    ssin=0;
    u=x;
    n=0;
    while abs(u)
        ssin=ssin+u;
        n=n+1;
        u=-u*x^2/((2*n)*(2*n+1));
    end
end