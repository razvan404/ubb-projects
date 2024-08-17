function pin=orto_poly_sym(w,x,a,b,n)
    pi0=sym(0); pi1=sym(1);
    int_pi1=int(w,a,b);
    alpha=int(x*pi1^2*w,a,b)/int_pi1;
    beta=int_pi1;
    for k=1:n
        pin=(x-alpha)*pi1-beta*pi0;
        pi0=pi1;pi1=pin;
        int_pi0=int_pi1;
        int_pi1=int(pi1^2*w,a,b);
        alpha=int(x*pi1^2*w,a,b)/int_pi1;
        beta=int_pi1/int_pi0;
    end
    pin=expand(pin);
end
