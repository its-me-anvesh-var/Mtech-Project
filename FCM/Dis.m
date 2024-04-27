% Dis(c)
% ----------------------------------------------

function Dis = Dis(X,c,V)

D_min = inf;
D_max = 0;
sum_fin = 0;

for i=1:c,
    sum_temp = 0;
    for j=1:c,
        temp = norm(V(i,:) - V(j,:));
        if temp ~=0,
            if temp < D_min,                
                D_min = temp;
            end
        end
        if temp > D_max,
            D_max = temp;
        end
        sum_temp = sum_temp + (temp^2);
    end
    sum_fin = sum_fin + (1/sum_temp);
end

Dis = (D_max * sum_fin) / D_min;