ds = collect(11:20)

k = Int(ds[1])
r = Int(ds[1])

for d in ds
    while k % d != 0
        k += r
    end

    r = lcm(r, d)
end

println(k)
