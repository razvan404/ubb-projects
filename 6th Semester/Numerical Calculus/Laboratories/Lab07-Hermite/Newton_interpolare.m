function L=Newton_interpolare(x,f,X)
    dif=dif_div(x,f);
    coefs=dif(1,:);
    L=[];
    for k=1:length(X)
        P=1; L(k)=coefs(1);
        for i=1:length(x)-1
            P=P*(X(k)-x(i));
            L(k)=L(k)+coefs(i+1)*P;
        end
    end
end