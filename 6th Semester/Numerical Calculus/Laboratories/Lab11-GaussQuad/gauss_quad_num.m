function [I,nodes,coefs]=gauss_quad_num(type,f,n,aa,bb)
    if nargin < 5, bb=[]; end
    if nargin < 4, aa=[]; end

    [alpha,beta]=orto_coef_num(type,0:n-1,aa,bb);
    J=diag(alpha)+diag(sqrt(beta(2:end)),-1)+diag(sqrt(beta(2:end)),1);
    [V,nodes]=eig(J,'vector');
    coefs=beta(1)*V(1,:).^2;
    I=coefs*f(nodes);
    nodes=nodes';
end