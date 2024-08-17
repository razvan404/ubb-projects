function S=evalsplinecubic(nodes,values,type,der_values,x)
    %examples of call:
    %c=splinecubic(nodes,values,'complete',[-1,1], x) % f'(a)=-1,f'(b)=1
    %c=splinecubic(nodes,values,'naturale', [], x) % f''(a)=f''(b)=0
    %c=splinecubic(nodes,values,'derivate2',[1,2], x) % f''(a)=1,f''(b)=2
    %c=splinecubic(nodes,values,'deBoor', [], x) % not-a-knot
    c=splinecubic(nodes,values,type,der_values);
    S=[];
    for i=1:length(x)
        if x(i)==nodes(end)
            S(i)=values(end);
        else
            poz=find(nodes>x(i),1)-1;
            X=x(i)-nodes(poz);
            S(i)=c(poz,1)+X*(c(poz,2)+X*(c(poz,3)+X*c(poz,4)));
        end
    end
end