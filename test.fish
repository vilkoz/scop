#!/usr/bin/fish

for i in (seq 10 20)
	rm test.obj
	for j in (seq $i)
		cat res/nanosuit.obj >> test.obj
	end
	wc -l test.obj
	time bash -c "./scop test.obj >> /dev/null" ^&1 | grep -oE '[0-9]*:[0-9]*\.[0-9]*elapsed'
end
