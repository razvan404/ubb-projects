function [Hx,der_Hx]=piecewise_cubic_hermite(nodes,values,der_values,x)
    Hx=x;der_Hx=x;
    for i=1:length(x)
        node_ind=find(nodes>x(i),1)-1;
        if ~isempty(node_ind) && node_ind>0 && node_ind<length(nodes)
        [Hx(i),der_Hx(i)]=Hermite_interp([nodes(node_ind),nodes(node_ind+1)],...
        [values(node_ind),values(node_ind+1)],[der_values(node_ind),der_values(node_ind+1)],x(i));
        elseif node_ind==0 
            Hx(i)=values(1);der_Hx(i)=der_values(1);
        else
            Hx(i)=values(end);der_Hx(i)=der_values(end);
        end
    end
end