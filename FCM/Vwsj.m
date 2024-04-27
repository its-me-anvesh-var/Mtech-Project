% The new validity index -> Vwsj(X,c,V,U,cmax,max_V) = Scat(c) + Sep(c)/Sep(Cmax)
% -----------------------------------------------------------------------

function Vwsj = Vwsj(X,c,V,U,cmax,max_V)

Scat_c = scat(X,c,V,U);
Sep_c = sep(X,c,V);
Sep_cmax = sep(X,cmax,max_V);

Vwsj = Scat_c + (Sep_c / Sep_cmax);