function y=least_sq_cont_Ceb1(f,n)
    %y(t)=c0*T0(t)+...+cn*Tn(t) este functia
    %care aprox. cel mai bine functia continua f(t)
    %in sensul celor mai mici patrate
    % unde T0,...,Tn sunt primele pol. Cebisev #1
    T=@(n,t) cos(n*acos(t));
    c0=integral(@(t) f(t)./sqrt(1-t.^2),-1,1)/pi;
    y=@(t) c0*T(0,t);
    for i=1:n
        ci=integral(@(t) T(i,t).*f(t)./sqrt(1-t.^2),-1,1)*2/pi;
        y=@(t) y(t)+ci*T(i,t);
    end
end