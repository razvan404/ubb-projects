function c=taylor_coef(f,n,a)
    if nargin < 3, a=0; end
    if n<0
        c=sym(0);
        return;
    end
    c=subs(diff(f,n),a)/factorial(n);
end
