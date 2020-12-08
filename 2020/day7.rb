
input = Hash.new
File.readlines('input/7').each do |line|
  matches = line.scan /(?:(\d+) )?(\w+ \w+) bags?/
  k = matches[0][1]
  d = Hash.new
  if matches[1][1] != 'no other'
    matches[1..].each { |count, bag| d[bag] = count.to_i }
  end
  input[k] = d
end

# inverted[k] is a set of bags that can hold k
@inverted = Hash.new { |h, k| h[k] = Set.new }
input.each { |k, v| v.each { |x, c| @inverted[x].add k } }

@visited = Set.new

def all_children(graph, start)
  to_visit = graph[start].to_a
  visited = Set.new(to_visit)

  until to_visit.empty?
    bag = to_visit.pop
    children = graph[bag].filter { |x| not visited.include? x }
    visited.merge(children)
    to_visit.concat(children)
  end

  visited
end

p all_children(@inverted, 'shiny gold').length

def count_bags(graph, start)
  graph[start].sum { |bag, count| count * (1 + count_bags(graph, bag)) }
end

p count_bags(input, 'shiny gold')