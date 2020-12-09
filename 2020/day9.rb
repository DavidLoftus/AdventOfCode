
PREAMBLE_SIZE = 25

def find_sum(a, n)
  i, j = 0, a.length - 1
  while i < j
    cmp = (a[i] + a[j]) <=> n
    if cmp < 0
      i += 1
    elsif cmp > 0
      j -= 1
    else
      return [i, j]
    end
  end
end

def find_contiguous_sum(a, n)
  i, j, sum = 0, 0, a[0]
  while sum != n and i < a.length and j < a.length
    if sum < n
      j += 1
      sum += a[j]
    else
      sum -= a[i]
      i += 1
    end
  end
  if sum == n
    [i, j]
  end
end

input = File.readlines('input/9').map(&:to_i)

first_invalid_index = (PREAMBLE_SIZE..input.length).find do |i|
  not find_sum(input[i-PREAMBLE_SIZE..i-1].sort, input[i])
end

first_invalid = input[first_invalid_index]
p first_invalid

lo, hi = find_contiguous_sum(input, first_invalid)
p input[lo..hi].min + input[lo..hi].max