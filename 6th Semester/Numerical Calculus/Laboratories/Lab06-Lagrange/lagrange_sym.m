 function L=lagrange_sym(nodes,values)
    syms x;
    L=sym(0);
    for k=1:length(nodes)
        L=L+values(k)*prod(x-nodes([1:k-1,k+1:end]))/prod(nodes(k)-nodes([1:k-1,k+1:end]));
    end
    L=expand(L);
end
