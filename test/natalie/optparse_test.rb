require_relative '../spec_helper'
require 'optparse'

describe 'OptionParser' do
  describe '#on' do
    it 'adds a new switch with a short and long name' do
      parser = OptionParser.new
      parser.on('-d', '--debug', 'enable debug mode')
      hash = {}
      parser.parse!(['foo', 'bar', '-d'], into: hash)
      hash.should == { debug: true }
    end

    it 'adds a new switch with short name and optional value' do
      parser = OptionParser.new
      parser.on('-d [level]', 'enable debug mode')
      hash = {}
      parser.parse!(['foo', '-d', 'verbose'], into: hash)
      hash.should == { 'd': 'verbose' }
    end

    it 'calls the block when matched' do
      options = {}
      parser = OptionParser.new
      parser.on('-d [level]', 'enable debug mode') do |value|
        options[:debug] = value
      end
      parser.parse!(['-d', 'verbose', 'foo'])
      options.should == { debug: 'verbose' }
    end
  end

  describe '#help' do
    it 'returns the help documentation' do
      parser = OptionParser.new do |opts|
        opts.banner = 'This is my test parser'
        opts.on('-d', '--debug [level]', 'enable debug mode')
        opts.on('-i', '--interactive', 'enable interactive mode')
      end
      expected = <<-END
This is my test parser
    -d, --debug [level]              enable debug mode
    -i, --interactive                enable interactive mode
END
      parser.help.should == expected
      parser.to_s.should == expected
    end
  end

  describe '--' do
    it 'stops parsing arguments' do
      parser = OptionParser.new
      parser.on('-d', 'enable debug mode')
      parser.on('-i', 'enable interactive mode')
      hash = {}
      args = ['-d', 'foo', '--', '-i', 'bar']
      parser.parse!(args, into: hash)
      hash.should == { 'd': true }
      args.should == ['foo', '-i', 'bar']
    end
  end
end
