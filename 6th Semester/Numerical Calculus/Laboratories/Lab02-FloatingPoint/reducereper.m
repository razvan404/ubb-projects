function y=reducereper(x,digits)
    if nargin < 2, digits=1144; end
    doipi=vpa(2*sym(pi),digits);
    x=vpa(x,digits);
    y=double(mod(x,doipi));
end 