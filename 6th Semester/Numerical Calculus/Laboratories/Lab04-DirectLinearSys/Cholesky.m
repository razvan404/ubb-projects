function R=Cholesky(A)
    n=length(A);
    R=A;
    for k=1:n
        for j=k+1:n
            R(j,j:n)=R(j,j:n)-R(k,j:n)*R(k,j)'/R(k,k);
        end
        R(k,k:n)=R(k,k:n)/sqrt(R(k,k));
    end
    R=triu(R);
end