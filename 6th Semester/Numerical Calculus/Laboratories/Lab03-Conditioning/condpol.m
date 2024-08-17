function nr_cond=condpol(coefs,xi)
    %numarul de cond. a aflarii rad. xi a unei ec. pol.
    %coefs=coeficientii pol.
    %apel de test:>>condpol(poly(1:n),xi)
    %poly(1:n)=coeficientii polinomului cu radacinile 1,...,n
    coefs_der=polyder(coefs); %coef. derivatei lui p;
    nr_cond=polyval(abs(coefs(2:end)),abs(xi))/abs(xi.*polyval(coefs_der,xi));
end
