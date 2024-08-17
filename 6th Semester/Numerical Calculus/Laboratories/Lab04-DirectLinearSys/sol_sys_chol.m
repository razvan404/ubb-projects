function x=sol_sys_chol(A,b)
    R=Cholesky(A);
    y=fwdsubs(R',b);
    x=bkwsubs(R,y);
end
