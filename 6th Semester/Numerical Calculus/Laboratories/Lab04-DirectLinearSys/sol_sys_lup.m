function x=sol_sys_lup(A,b)
    [L,U,P]=lup(A);
    y=fwdsubs(L,P*b);
    x=bkwsubs(U,y);
end
