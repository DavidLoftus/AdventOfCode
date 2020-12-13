def extended_gcd(a, b)
  last_remainder, remainder = a.abs, b.abs
  x, last_x, y, last_y = 0, 1, 1, 0
  while remainder != 0
    last_remainder, (quotient, remainder) = remainder, last_remainder.divmod(remainder)
    x, last_x = last_x - quotient*x, x
    y, last_y = last_y - quotient*y, y
  end
  return last_remainder, last_x * (a < 0 ? -1 : 1)
end

def invmod(e, et)
  g, x = extended_gcd(e, et)
  if g != 1
    raise 'Multiplicative inverse modulo does not exist!'
  end
  x % et
end

def chinese_remainder(mods, remainders)
  max = mods.inject( :* )  # product of all moduli
  series = remainders.zip(mods).map{ |r,m| (r * max * invmod(max/m, m) / m) }
  series.inject( :+ ) % max
end

min, id_string = IO.readlines('input/13')
min, ids = min.to_i, id_string.split(',').filter{ |x| x != 'x' }.map(&:to_i)

best_bus = ids.max_by { |id| min % id }
wait_time = best_bus - min % best_bus
p best_bus * wait_time

id_groups = id_string.split(',').each_with_index.filter { |x, i| x != 'x' }.map { |x, i| [x.to_i, i] }
p id_groups

n = id_groups.map(&:first)
a = id_groups.map { |ni, ai| (ni - ai) % ni }

p n, a
t = chinese_remainder(n, a)
p t