function [w,a,b]=weights_and_bounds(type, aa, bb)
    if nargin < 3, bb=[]; end
    if nargin < 2, aa=[]; end
    
    syms x;
    switch type
    case 'Legendre'
        a=-sym(1);b=sym(1);
        w=sym(1);
    case 'Cebisev1'
        a=-sym(1);b=sym(1);
        w=1/sqrt(1-x^2);
    case 'Cebisev2'
        a=-sym(1);b=sym(1);
        w=sqrt(1-x^2);
    case 'Jacobi'
        a=-sym(1);b=sym(1);
        w=(1-x)^aa*(1+x)^bb;
    case 'Laguerre'
        a=sym(0);b=sym(Inf);
        w=x^aa*exp(-x);
    case 'Hermite'
        a=-sym(Inf);b=sym(Inf);
        w=exp(-x^2);
    end
end