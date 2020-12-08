# a=$<.map{|l|l.tr('FBLR','0101').to_i 2}.sort
# p a[-1],a.each_cons(2).find{|a,b|a==b-2}[0]+1

input = File.readlines('input/5')
            .map { |line| [line[0..6], line[7..9]] }
            .map { |r, c| [r.tr('FB', '01').to_i(2), c.tr('LR', '01').to_i(2)] }

ids = input.map { |r,c| r*8 + c }

p ids.max

ids.sort!

ids.each_with_index do |id, i|
  if ids[i+1] == id + 2
    p id + 1
  end
end