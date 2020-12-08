input = File.open('input/8').map do |line|
  op, val = line.split
  val = val.to_i
  [op, val]
end

def simulate(program, history = nil, pc = 0, acc = 0)
  history = history ? history : Set[]

  pc, acc = 0, 0
  while program[pc] and not history.include? pc
    op, val = program[pc]
    history.add(pc)

    if op == 'acc'
      acc += val
    elsif op == 'jmp'
      pc += val - 1
    end
    pc += 1
  end

  [acc, !history.include?(pc)]
end

p simulate(input)[0]

input.filter { |op, _| op == 'jmp' or op == 'nop' }.each do |inst|
  inst[0] = inst[0] == 'jmp' ? 'nop' : 'jmp'
  acc, terminated = simulate(input)
  if terminated
    p acc
  end
  inst[0] = inst[0] == 'jmp' ? 'nop' : 'jmp'
end