input = File.open('input/1').readlines.map(&:to_i)

def part1(input)
  input = input.sort

  i,j = 0, input.size-1
  while i < j
    sum = input[i] + input[j]
    if sum == 2020
      break
    elsif sum < 2020
      i += 1
    else
      j -= 1
    end
  end

  input[i] * input[j]
end

def part2(input)
  input = input.sort
  input.each do |x|
    i,j = 0, input.size-1
    while i < j
      sum = input[i] + input[j]
      if sum == 2020-x
        break
      elsif sum < 2020-x
        i += 1
      else
        j -= 1
      end
    end

    if i < j
      return x * input[i] * input[j]
    end
  end
end

puts part1(input)
puts part2(input)
