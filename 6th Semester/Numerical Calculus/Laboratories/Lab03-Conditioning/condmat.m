function c=condmat(A,p)
    if nargin < 2, p=2; end
    c=pnorm(A,p) * pnorm(inv(A), p);
end

