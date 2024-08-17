function pin=orto_poly_sym_type(type,n,aa,bb)
    if nargin < 4, bb=[]; end
    if nargin < 3, aa=[]; end
    
    syms x;
    pi0=sym(0); pi1=sym(1);
    [alpha,beta]=orto_coef_sym_type(type,sym(0:n-1),aa,bb);
    for k=1:n
        pin=(x-alpha(k))*pi1-beta(k)*pi0;
        pi0=pi1; pi1=pin;
    end
    pin=expand(pin);
end
