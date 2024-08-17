function x=bkwsubs(A,b)
    x=b;
    for i=length(b):-1:1
        x(i)=(b(i)-A(i,i+1:end)*x(i+1:end))/A(i,i);
    end
end
