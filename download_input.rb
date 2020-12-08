require 'httparty'


raise 'missing environment variable AOC_COOKIE' unless ENV.key?('AOC_COOKIE')

SESSION_COOKIE = ENV['AOC_COOKIE']
INPUT_URL = 'https://adventofcode.com/%d/day/%d/input'

def get_input(year, day)
  out_path = "#{year}/input/#{day}"
  unless File.exists?(out_path)
    resp = HTTParty.get(
        INPUT_URL % [year, day],
        headers: { 'Cookie': "session=#{SESSION_COOKIE}" }
    )
    open(out_path, 'w') do |f|
      f << resp.body
    end
  end
end

(2017..2020).each do |year|
  (1..25).each do |day|
    d = Date.new(year, 12, day)
    get_input(year, day) if d <= DateTime.now
  end
end
