d = collect(1:100)
r = abs(reduce(-, map(sum, [d .^ 2, sum(d) ^ 2])))
println(r)
