input = File.readlines('input/2').map do |line|
  policy, password = line.split ': '
  range, letter = policy.split
  min, max = range.split('-').map(&:to_i)
  [min, max, letter, password]
end

valid = input.filter do |min, max, l, p|
  (min..max).include?(p.chars.count { |c| c == l })
end
puts valid.size

valid = input.filter do |min, max, l, p|
  (p[min-1] == l) != (p[max-1] == l)
end
puts valid.size