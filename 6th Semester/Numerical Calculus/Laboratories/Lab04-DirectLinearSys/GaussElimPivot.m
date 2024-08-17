function x=GaussElimPivot(A,b)
    A=[A b];
    for i=1:length(b)-1
        [maxval,maxpos]=max(abs(A(i:end,i)));
        pivpos=maxpos+i-1;
        if maxval>0&&pivpos~=i
            A([i pivpos],i:end)=A([pivpos i],i:end);
        elseif maxval==0
            disp('No unique solution!');
        end
        for k=i+1:length(b)
            A(k,i:end)=A(k,i:end)-(A(k,i)/A(i,i))*A(i,i:end);
        end
    end
    x=bkwsubs(A(:,1:end-1),A(:,end));
end
