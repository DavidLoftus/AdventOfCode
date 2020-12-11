
input = File.readlines('input/11').map{ |l| l.chomp.chars }

def find_seat(st, i, j, di, dj)
  if (0...st.length).include?(i+di) and (0...st[0].length).include?(j+dj)
    if st[i+di][j+dj] == '.'
      find_seat(st, i+di, j+dj, di, dj)
    else
      st[i+di][j+dj]
    end
  end
end

def count_neighbours(st, i, j)
  r = (-1..1).to_a.product((-1..1).to_a) - [[0,0]]
  r.count { |di, dj| (0...st.length).include?(i+di) and (0...st[0].length).include?(j+dj) and st[i+di][j+dj] == '#' }
end

def count_visible_neighbours(st, i, j)
  r = (-1..1).to_a.product((-1..1).to_a) - [[0,0]]
  r.count { |di, dj| find_seat(st, i, j, di, dj) == '#' }
end

def next_state(st, count_neighbours, limit)
  st.each_with_index.map do |row, i|
    row.each_with_index.map do |c, j|
      count = count_neighbours.call(st, i, j)
      if c == 'L' and count == 0
        '#'
      elsif c == '#' and count >= limit
        'L'
      else
        c
      end
    end
  end
end

def find_equilibrium(s, count_neighbours = method(:count_neighbours), limit=4)
  # puts s.map(&:join).join "\n"
  # puts '-------'
  ns = next_state(s, count_neighbours, limit)
  if s == ns
    s
  else
    find_equilibrium(ns, count_neighbours, limit)
  end
end

s = find_equilibrium(input)
p s.sum { |row| row.count('#') }

s = find_equilibrium(input, method(:count_visible_neighbours), 5)
p s.sum { |row| row.count('#') }