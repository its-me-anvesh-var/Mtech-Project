% The validity index -> Vxie(X,c,V,U,m) = (sum<k=1~n>{ sum<i=1~c>{ (Uik ^ m) *
%                       (||Vi - Xk||^m) } }) / (n * min||Vi - Vj||)
%                       where i ~= j
% -------------------------------------------------------------------------

function Vxie = Vxie(X,c,V,U,m)

sum_fin = 0;
n = size(U,2);
V_mean = sum(V) / n;
min_V = inf;

for i=1:c,    
    for k=1:n,
        tmp_1 = U(i,k)^m;
        tmp_2 = (norm(V(i,:) - X(k,:)))^m;
        sum_fin = sum_fin + (tmp_1 * tmp_2);
    end

    for j=1:c,
        tmp_V = norm(V(i) - V(j));
        if tmp_V ~= 0,
            if tmp_V < min_V,
                min_V = tmp_V;
            end
        end
    end
end

Vxie = sum_fin / (n * min_V);