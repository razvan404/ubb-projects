function [coefs,err]=least_sq(x,f,k)
    A=ShortVander(x,k+1);
    [coefs,err]=linsys2(A,f');
end