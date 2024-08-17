 function coefs=gauss_coefs_sym(w,a,b,nodes)
    syms x;
    coefs=sym([]);
    n=length(nodes);
    for k=1:n
        coefs(k)=simplify(int(prod(x-nodes([1:k-1,k+1:n]))...
                *w,a,b)/prod(nodes(k)-nodes([1:k-1,k+1:n])));
    end
 end
