function x=GaussSeidel_it(A,b,NrIt)
  n=length(b);
  x=zeros(n,1);
  x_old=x;
  for k=1:NrIt
    for i=1:n
     x(i)=(b(i)-A(i,1:i-1)*x(1:i-1)...
          -A(i,i+1:n)*x_old(i+1:n))/A(i,i);
    end
    x_old=x;
  end
end
