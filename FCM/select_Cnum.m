%  Interface for multi-testing
function c_n = select_Cnum(data,v_index,times,options)

% Change the following to set default options
default_options =   [2;	% exponent for the partition matrix U
                    1000;	% max. number of iteration
                    1e-3;	% min. amount of improvement
                    0];	% info display during iteration 
    
if nargin == 3,
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

temp_cn = zeros(times,1);

% run by v_index
switch v_index

case 'Vpc'
    for iter=1:times,
        temp_cn(iter,1) = C_num_S_Vpc(data,options);
    end
case 'Vpe'
    for iter=1:times,
        temp_cn(iter,1) = C_num_S_Vpe(data,options);
    end
case 'Vxie'
    for iter=1:times,
        temp_cn(iter,1) = C_num_S_Vxie(data,options);
    end
case 'Vfs'
    for iter=1:times,
        temp_cn(iter,1) = C_num_S_Vfs(data,options);
    end
 case 'Vrlr'
    for iter=1:times,
        temp_cn(iter,1) = C_num_S_Vrlr(data,options);
    end    
 case 'Vwsj'
    for iter=1:times,
        temp_cn(iter,1) = C_num_S_Vwsj(data,options);
    end     
otherwise
  error(['Unknown validity index ', v_index]);               
end

c_n = temp_cn;