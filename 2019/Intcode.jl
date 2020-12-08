using DataStructures

mutable struct Intcode
    memory::Array{BigInt}
    pc::Int
    
    input::Queue{<:Integer}
    output::Queue{<:Integer}
    
    relBase::Int
    
    Intcode(program::AbstractArray{Int}, input = Queue{BigInt}(), output = Queue{Int}()) = new(copy(program), 1, input, output, 0)
end

isdone(cpu::Intcode) = readMem(cpu, cpu.pc-1) == 99
needsinput(cpu::Intcode) = readMem(cpu, cpu.pc-1) == 3

function readNextInt(cpu::Intcode)
    ret = readMem(cpu, cpu.pc-1)
    cpu.pc += 1
    return ret
end

readOpCode(cpu::Intcode) = divrem(readNextInt(cpu), 100)
function readParam(cpu::Intcode, paramMode)
    val = readNextInt(cpu)
    mode = paramMode % 10
    if mode == 0
        readMem(cpu, val)
    elseif mode == 1
        val
    elseif mode == 2
        return readMem(cpu, cpu.relBase+val)
    else
        throw("unknown mode $mode")
    end
end

function readAddr(cpu::Intcode, paramMode)
    val = readNextInt(cpu)
    mode = paramMode % 10
    if mode == 0
        val
    elseif mode == 2
        cpu.relBase+val
    else
        throw("unknown mode $mode")
    end
end


function writeToMem(cpu::Intcode, addr, val)
    if length(cpu.memory) < addr+1
        l = length(cpu.memory)
        resize!(cpu.memory, addr+1)
        cpu.memory[l+1:end] .= 0
    end
    cpu.memory[addr+1] = val
end

function readMem(cpu::Intcode, addr)
    if length(cpu.memory) < addr+1
        return 0
    end
    return cpu.memory[addr+1]
end

function next!(cpu::Intcode)
    params, opcode = readOpCode(cpu)
    if opcode == 1
        a = readParam(cpu, params)
        b = readParam(cpu, params ÷ 10)
        c = readAddr(cpu, params ÷ 100)
        # println("[$c] = $a + $b")
        writeToMem(cpu, c, a+b)
    elseif opcode == 2
        a = readParam(cpu, params)
        b = readParam(cpu, params ÷ 10)
        c = readAddr(cpu, params ÷ 100)
        # println("[$c] = $a * $b")
        writeToMem(cpu, c, a*b)
    elseif opcode == 3
        a = readAddr(cpu, params)
        # println("input [$a]")
        writeToMem(cpu, a, dequeue!(cpu.input))
    elseif opcode == 4
        a = readParam(cpu, params)
        # println("output $a")
        enqueue!(cpu.output, a)
    elseif opcode == 5
        a = readParam(cpu, params)
        b = readParam(cpu, params ÷ 10)
        # println("jump to $b if $a != 0")
        if a != 0
            cpu.pc = b+1
        end
    elseif opcode == 6
        a = readParam(cpu, params)
        b = readParam(cpu, params ÷ 10)
        # println("jump to $b if $a == 0")
        if a == 0
            cpu.pc = b+1
        end
    elseif opcode == 7
        a = readParam(cpu, params)
        b = readParam(cpu, params ÷ 10)
        c = readAddr(cpu, params ÷ 100)
        # println("[$c] = $a < $b")
        writeToMem(cpu, c, a < b ? 1 : 0)
    elseif opcode == 8
        a = readParam(cpu, params)
        b = readParam(cpu, params ÷ 10)
        c = readAddr(cpu, params ÷ 100)
        # println("[$c] = $a == $b")
        writeToMem(cpu, c, a == b ? 1 : 0)
    elseif opcode == 9
        a = readParam(cpu, params)
        # println("relBase = relBase + $a = $(cpu.relBase + a)")
        cpu.relBase += a
    elseif opcode == 99
        return
    else
        throw("Unknown opcode $opcode")
    end
end