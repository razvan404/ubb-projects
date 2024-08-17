function area=reprectangle(f,a,b,n)
    h=(b-a)/n; 
    x_mid=a+h/2:h:b-h/2;
    area=h*sum(f(x_mid));
end
