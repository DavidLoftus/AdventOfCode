
DIRECTIONS = [[1, 0], [0, 1], [-1, 0], [0, -1]]

input = IO.readlines('input/12').map { |line| [line[0], line[1..].to_i] }

pos = 0
dir = 1
input.each do |op, val|
  case op
  when 'N'
    pos += val * 1i
  when 'S'
    pos -= val * 1i
  when 'E'
    pos += val
  when 'W'
    pos -= val
  when 'L'
    dir *= 1i ** (val / 90)
  when 'R'
    dir *= (-1i) ** (val / 90)
  when 'F'
    pos += val * dir
  else
    raise "unknown op #{op} #{val}"
  end
end

p pos.rect.map(&:abs).sum

pos = 0
dir = 10 + 1i
input.each do |op, val|
  case op
  when 'N'
    dir += val * 1i
  when 'S'
    dir -= val * 1i
  when 'E'
    dir += val
  when 'W'
    dir -= val
  when 'L'
    dir *= 1i ** (val / 90)
  when 'R'
    dir *= (-1i) ** (val / 90)
  when 'F'
    pos += val * dir
  else
    raise "unknown op #{op} #{val}"
  end
end

p pos.rect.map(&:abs).sum