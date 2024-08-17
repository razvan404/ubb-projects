function I=gauss_quad_num_ceb1(f,n)
    k=1:n;
    nodes=cos((2*k-1)/(2*n)*pi);
    I=pi/n*sum(f(nodes));
end