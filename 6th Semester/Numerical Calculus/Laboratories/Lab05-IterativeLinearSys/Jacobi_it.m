function x=Jacobi_it(A,b,NrIt)
  x_old=zeros(size(b));
  x=x_old;
  for k=1:NrIt
    for i=1:length(b)
     x(i)=(b(i)-A(i,1:i-1)*x_old(1:i-1)...
          -A(i,i+1:end)*x_old(i+1:end))/A(i,i);
    end
    x_old=x;
  end
end
