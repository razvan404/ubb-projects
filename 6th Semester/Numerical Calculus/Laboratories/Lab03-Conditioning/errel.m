function d=errel(x,xp,p)
    if nargin < 3, p=2; end
    d=norm(x-xp,p)/norm(x,p);
end