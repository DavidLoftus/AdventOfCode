
class Passport
  def initialize(fields)
    @fields = fields
  end

  def self.parse(s)
    h = Hash.new
    s.split.map{ |entry| entry.split ':' }.each { |k,v| h[k] = v }
    Passport.new(h)
  end

  def fields_exist?
    %w[byr iyr eyr hgt hcl ecl pid].all? { |k| @fields.key? k }
  end

  def fields_valid?
    return false unless fields_exist?
    return false unless (1920..2002).include? @fields['byr'].to_i \
                    and (2010..2020).include? @fields['iyr'].to_i \
                    and (2020..2030).include? @fields['eyr'].to_i

    m = @fields['hgt'].match /^(\d+)(cm|in)$/
    return false unless m
    return false unless (m[2] == 'cm' and (150..193).include? m[1].to_i) \
                     or (m[2] == 'in' and ( 59.. 76).include? m[1].to_i)

    return false unless @fields['hcl'].match? /^#[0-9a-f]{6}$/
    return false unless %w[amb blu brn gry grn hzl oth].include? @fields['ecl']
    return false unless @fields['pid'].match? /^[0-9]{9}$/

    true
  end
end

def parse_passport(line)

end

input = File.read('input/4').split("\n\n").map { |line| Passport.parse line }

p input.count(&:fields_exist?)
p input.count(&:fields_valid?)