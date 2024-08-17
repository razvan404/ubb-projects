function [Q,R]=Householder(A)
    [m,n]=size(A);
    Q=eye(m);
    P=[eye(n);zeros(m-n,n)];
    for j=1:n
        u=[zeros(j-1,1); A(j:m,j)];
        s=norm(u);
        x1=u(j);
        if x1
            u(j)=sign(x1)*(abs(x1)+s);
        else
            u(j)=s;
        end
        P=eye(m)-(u*u')/(s*(s+abs(x1)));
        Q=Q*P;
        A=P*A;
    end
    R=triu(A);
end
