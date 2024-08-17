function y=mysin(x,digits)
    if nargin < 2, digits=1000; end

    x=reducereper(x,digits); 
    semn=1;
    if x>3*pi/2
        x=2*pi-x; semn=-1;
    elseif x>pi
        x=x-pi; semn=-1;
    elseif x>pi/2
        x=pi-x;
    end

    if x<=pi/4
        y=sinred(x);
    else
        y=cosred(pi/2-x);
    end
    
    y=semn*y;
end