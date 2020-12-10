input = IO.readlines('input/10').map(&:to_i)
input.sort!

count_map = Hash.new(0)
[0, *input, input[-1] + 3].each_cons(2) { |a,b| count_map[b-a] += 1 }

p count_map[1] * count_map[3]

def hill_climb(f, n)
  i, a, b, c = 0, 0, 0, 1
  while i < n
    if f.include?(i)
      i, a, b, c = i + 1, b, c, a + b + c
    else
      i, a, b, c = i + 1, b, c, 0
    end
  end
  a + b + c
end

p hill_climb(Set.new(input), input[-1] + 3)