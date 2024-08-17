function [H,dH]=Hermite_interpolare(x,f,df,X)
    dif=dif_div_duble(x,f,df);
    coefs=dif(1,:);
    z=repelem(x,2);
    H=[];dH=[];
    for k=1:length(X)
        P=1; DP=0; H(k)=coefs(1); dH(k)=0;
        for i=1:length(z)-1
            DP=DP*(X(k)-z(i))+P;
            P=P*(X(k)-z(i));
            H(k)=H(k)+coefs(i+1)*P;
            dH(k)=dH(k)+coefs(i+1)*DP;
        end
    end
end