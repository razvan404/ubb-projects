function area=reptrapezium(f,a,b,n)
    h=(b-a)/n; 
    x=a+h:h:b-h;
    area=h/2*(f(a)+f(b)+2*sum(f(x)));
end
