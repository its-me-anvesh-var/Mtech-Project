% FCM-based model selection algorithm using VRLR
% Optimal cluster number c = arg( Min{VRLR(c)} )

function cluster_num = C_num_S_Vrlr(data, options)

% Change the following to set default options
default_options =   [2;	% exponent for the partition matrix U
                    1000;	% max. number of iteration
                    1e-3;	% min. amount of improvement
                    0];	% info display during iteration 
    
if nargin == 1,
	options = default_options;
else
	% If "options" is not fully specified, pad it with default values.
	if length(options) < 4,
		tmp = default_options;
		tmp(1:length(options)) = options;
		options = tmp;
	end
	% If some entries of "options" are nan's, replace them with defaults.
	nan_index = find(isnan(options)==1);
	options(nan_index) = default_options(nan_index);
	if options(1) <= 1,
		error('The exponent should be greater than 1!');
	end
end

Cmin = 2;
n = size(data,1);
Cmax = floor(sqrt(n));
Vd = zeros(Cmax,1);

[max_center, max_U, max_obj_fcn] = fcm(data, Cmax, options);
alpha = Dis(data,Cmax,max_center);

for i=Cmin:Cmax,
    [center, U, obj_fcn] = fcm(data, i, options);
    Vd(i,1) = Vrlr(data,i,center,U,alpha);
end
Vd(1,1) = inf;
Vd
[Y,I] = min(Vd);
cluster_num = I;