function [rest, gr_maxim]=rest_gauss_fara_f(w,a,b,pi,n,type)
    % Pentru a afla restul real, trebuie inmultit cu f^(gr_maxim+1)(\csi),
    % unde \csi se alege astfel incat sa fie worst case pentru f^(gr_maxim+1)
    % w: functia pondere (nu cea initiala, ptr Radau/Lobatto inmultita
    %    (x-a)/(b-x) / (x-a)(b-x))
    % a, b: capetele intervalului de la integrala
    % pi: polinomul de grad n ortogonal pe [a,b] in raport cu ponderea w
    % n: gradul lui pi / gradul + 1 pentru Radau / graul + 2 ptr Lobatto
    % type: nimic / Radau / Lobatto
    if nargin < 6
        gr_maxim=2*n-1;
    elseif type == "Radau"
        gr_maxim=2*n-2;
    elseif type == "Lobatto"
        gr_maxim=2*n-3;
    else
        disp("tip invalid")
        exit(1)
    end
    rest=int(w*pi^2, a, b)/factorial(sym(gr_maxim+1));
end