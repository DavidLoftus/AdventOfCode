
input = File.read('input/6').split("\n\n").map { |x| x.split("\n").map { |y| Set.new(y.chars) } }

p input.map { |group| group.inject(:|).count }.sum

p input.map { |group| group.inject(:&).count }.sum