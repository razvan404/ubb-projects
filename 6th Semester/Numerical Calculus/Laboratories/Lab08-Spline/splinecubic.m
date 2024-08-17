function c=splinecubic(nodes,values,type,der_values)
    %c=the coefficients of the cubic spline of the given type
    %examples of call:
    %c=splinecubic(nodes,values,'complete',[-1,1]) % f'(a)=-1,f'(b)=1
    %c=splinecubic(nodes,values,'naturale') % f''(a)=f''(b)=0
    %c=splinecubic(nodes,values,'derivate2',[1,2]) % f''(a)=1,f''(b)=2
    %c=splinecubic(nodes,values,'deBoor') % not-a-knot
    n=length(nodes);
    c=[];
    dx=diff(nodes)'; ddiv=diff(values)'./dx;
    A=zeros(n);b=zeros(n,1);
    for i=2:n-1
        A(i,i-1:i+1)=[dx(i),2*(dx(i-1)+dx(i)),dx(i-1)];
        b(i)=3*(dx(i)*ddiv(i-1)+dx(i-1)*ddiv(i));
    end
    switch type
    case 'complete'
        A(1,1)=1;A(n,n)=1;
        b(1)=der_values(1);b(n)=der_values(2);
    case 'naturale'
        A(1,1:2)=[2 1];A(n,n-1:n)=[1 2];
        b(1)=3*ddiv(1);b(n)=3*ddiv(n-1);
    case 'derivate2'
        A(1,1:2)=[2 1];A(n,n-1:n)=[1 2];
        b(1)=3*ddiv(1)-der_values(1)*dx(1)/2;
        b(n)=3*ddiv(n-1)+der_values(2)*dx(n-1)/2;
    case 'deBoor'
        A(1,1:3)=[dx(2)^2 dx(2)^2-dx(1)^2 -dx(1)^2];
        b(1)=2*(ddiv(1)*dx(2)^2-ddiv(2)*dx(1)^2);
        A(n,n-2:n)=[dx(n-1)^2 dx(n-1)^2-dx(n-2)^2 -dx(n-2)^2];
        b(n)=2*(ddiv(n-2)*dx(n-1)^2-ddiv(n-1)*dx(n-2)^2);
    end
    m=A\b;
    c(:,1)=values(1:n-1);
    c(:,2)=m(1:n-1);
    c(:,4)=(m(2:n)+m(1:n-1)-2*ddiv)./(dx.^2);
    c(:,3)=(ddiv-m(1:n-1))./dx-c(:,4).*dx;
end
