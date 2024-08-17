function [x,ni,rho]=GaussSeidel(A,b,err,p)
    if nargin < 4, p=Inf; end
    if nargin < 3, err=1e-14; end
    
    M=tril(A);
    N=M-A;T=M\N;c=M\b;
    rho=max(abs(eig(T))); 
    while norm(T,p)>=1
        fprintf('norm(T,p)=%f\n',norm(T,p));
        p=input("Dati alt p a.i. norm(T,p))<1:");
    end
    factor=norm(T,p)/(1-norm(T,p));
    x_old=zeros(size(b)); ni=1;
    x=x_old;
    while ni<1e+4
        x=T*x_old+c;
        if norm(x-x_old,p)*factor<=err
            return;
        else  
            ni=ni+1;
            x_old=x;
        end
    end
end
