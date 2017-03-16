r = sum(filter(x -> x % 3 == 0 || x % 5 == 0,  1:1000-1))
println(r)
