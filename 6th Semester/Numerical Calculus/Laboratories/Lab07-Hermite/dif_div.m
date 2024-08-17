function T=dif_div(x,f)
    T=NaN(length(x));
    T(:,1)=f';
    for j=2:length(x)
        for i=1:length(x)+1-j
             T(i,j)=(T(i+1,j-1)-T(i,j-1))/(x(i+j-1)-x(i));
        end
    end
end