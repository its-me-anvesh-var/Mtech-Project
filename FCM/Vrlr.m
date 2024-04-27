% The new validity index -> VRLR(X,c,V,U,alpah) = alpha * Scat(c) + Dis(c)
%                           where alpha = Dis(cmax)
% -----------------------------------------------------------------------

function VRLR = Vrlr(X,c,V,U,alpha)

Scat_c = scat(X,c,V,U);
Dis_c = Dis(X,c,V);

VRLR = (alpha * Scat_c) + Dis_c;