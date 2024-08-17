function L=LagrangeBary(x,f,X,type)
    %noduri: x=[x1,...,xn]
    %valori in noduri: f=[f(x1),...,f(xn)]
    %L=valoarea pol. Lagrange in vectorul X
    %type='none','echidistante','Cebisev1','Cebisev2'
    if nargin < 4, type='none'; end
    w=CoeffBary(x,type);
    L=zeros(size(X));
    for k=1:length(X)
        x_pos_nod=find(x==X(k));
        %pozitia nodului care este egal cu X(k)
        if x_pos_nod
            L(k)=f(x_pos_nod);
        else
            L(k)=sum(w.*f./(X(k)-x))/sum(w./(X(k)-x));
        end
    end
end
