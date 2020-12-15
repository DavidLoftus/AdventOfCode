class Mask
  def initialize(s)
    @control_mask = s.tr('01X', '001').to_i 2
    @data_mask = s.tr('01X', '010').to_i 2
  end

  def mask(x)
    (x & @control_mask) | @data_mask
  end

  def mask_v2(x)
    recursive_mask(x | @data_mask, @control_mask)
  end

  private
  def recursive_mask(x, control)
    possible_values = Set.new
    36.times do |i|
      bit = 1 << i
      if control & bit != 0
        possible_values |= recursive_mask(x & ~bit, control & ~bit)
        possible_values |= recursive_mask(x | bit, control & ~bit)
        break
      end
    end
    possible_values.empty? ? [x] : possible_values
  end
end

mem = Hash.new
mask = nil
IO.foreach('input/14') do |line|
  if /mask = ([01X]+)/ =~ line
    mask = Mask.new($~[1])
  elsif /mem\[(\d+)\] = (\d+)/ =~ line
    mem[$~[1].to_i] = mask.mask($~[2].to_i)
  end
end

p mem.values.sum


mem = Hash.new
mask = nil
IO.foreach('input/14') do |line|
  if /mask = ([01X]+)/ =~ line
    mask = Mask.new($~[1])
  elsif /mem\[(\d+)\] = (\d+)/ =~ line
    val = $~[2].to_i
    puts "mem[#{$~[1].to_i}] = #{val}"
    mask.mask_v2($~[1].to_i).each { |i| mem[i] = val }
  end
end

p mem.values.sum