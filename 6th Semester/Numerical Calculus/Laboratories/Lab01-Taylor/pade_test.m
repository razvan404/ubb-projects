function pade_test(f,x,m,k,a,b)
    if nargin < 6, b=1; end
    if nargin < 5, a=-1; end
    fh=matlabFunction(f);
    R=pade_sym(f,m,k,x)
    Rh=matlabFunction(R);
    T=taylor(f,x,0,'order',m+k+1)
    Th=matlabFunction(T);
    clf;hold on;grid on;
    fplot(fh,[a,b],'-g','linewidth',2);
    fplot(Rh,[a,b],'--b','linewidth',1.5);
    fplot(Th,[a,b],'--r','linewidth',1.5);
    h=legend({'f','Pade','Taylor'},'location','northeastoutside');
    set(h,'fontsize',15);
end