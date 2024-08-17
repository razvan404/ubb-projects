function T=taylor_draw(f,a,b,n,k)
    if nargin < 5, k=0; end
    clf; hold on; grid on;
    fh=matlabFunction(f);
    fplot(fh,[a,b]);
    L={'f'};
    for i=1:n
        T=taylor(f,'order',i+1,'ExpansionPoint',k);
        Th=matlabFunction(T);
        fplot(Th,[a,b]);
        L{end+1}=['T' num2str(i)];
    end
    legend(L,'location','northeastoutside');
end