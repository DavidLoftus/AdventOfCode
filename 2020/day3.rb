
input = File.readlines('input/3').map{|l| l.chomp.chars.map{|c|c == '#'} }

def traverse(input, slope_i, slope_j)
  i, j = 0, 0
  count = 0
  while i + slope_i < input.length
    i += slope_i
    j += slope_j
    count += 1 if input[i][j % input[i].length]
  end
  count
end

p traverse(input, 1, 3)

slopes = [[1, 1], [1, 3], [1, 5], [1, 7], [2, 1]]

p slopes.map { |i, j| traverse(input, i, j) }.inject(:*)