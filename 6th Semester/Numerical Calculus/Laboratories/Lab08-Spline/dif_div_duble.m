function T=dif_div_duble(x,f,df)
    T=NaN(2*length(x));
    z=repelem(x,2);
    T(:,1)=repelem(f,2);
    T(1:2:end,2)=df;
    T(2:2:end-2,2)=diff(f)./diff(x);
    for j=3:length(z)
        for i=1:length(z)+1-j
            T(i,j)=(T(i+1,j-1)-T(i,j-1))/(z(i+j-1)-z(i));
        end
    end
end