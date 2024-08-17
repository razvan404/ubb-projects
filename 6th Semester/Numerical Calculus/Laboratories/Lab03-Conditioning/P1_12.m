%% P1_12
% Conditionarea radacinilor multiple ale unei ecuatii polinomiale

close all
format short g
xi=1:20;
rr=[xi;xi];
pm=poly(rr(:));
m=2*ones(size(xi));
nc=condpolmult(pm,xi,m);
[ncs,i]=sort(nc');
[ncs,i]
%% Perturbatie normala
subplot(1,2,1)
wilkinsond(20)
title('normal')

%% Perturbatie uniforma
subplot(1,2,2)
wilkinsondu(20)
title('uniform')