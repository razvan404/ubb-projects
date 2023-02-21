function back(v, k, curr, niv, ok)
	if niv == k
		disp(curr)
	else
		for i=1:length(v)
			if ok(i) == 0
				ok(i)=1;
				curr(end + 1)=v(i);
				back(v, k, curr, niv+1, ok);
				curr(end)=[];
				ok(i)=0;
			end
		end
	end
end

function aranjamente(v, k)
	ok=zeros(length(v));
	back(v, k, [], 0, ok)
end

