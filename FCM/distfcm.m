function out = distfcm(center, data)
%DISTFCM Distance measure in fuzzy c-mean clustering.
%	OUT = DISTFCM(CENTER, DATA) calculates the Euclidean distance
%	between each row in CENTER and each row in DATA, and returns a
%	distance matrix OUT of size M by N, where M and N are row
%	dimensions of CENTER and DATA, respectively, and OUT(I, J) is
%	the distance between CENTER(I,:) and DATA(J,:).
%
%       See also FCMDEMO, INITFCM, IRISFCM, STEPFCM, and FCM.

%	Roger Jang, 11-22-94.
%       Copyright (c) 1994-95  by The MathWorks, Inc.
%       $Revision: 1.4 $  $Date: 1995/02/17 13:08:10 $

out = zeros(size(center, 1), size(data, 1));

% fill the output matrix
for k = 1:size(center, 1),
	out(k, :) = sqrt(sum(((data-ones(size(data, 1), 1)*center(k, :)).^2)'));
end
