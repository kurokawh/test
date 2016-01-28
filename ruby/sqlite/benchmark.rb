require 'sqlite3'
require 'sequel'

def create_database()
	puts 'create_database()'

	DB.create_table :table_100k_noindex do
		Integer	:col0
		Integer	:col1
		String :col2
	end

	DB.create_table :table_100k_index do
		Integer	:col0
		Integer	:col1
		String :col2
		index :col0
	end

	DB.create_table :table_100k_two_index do
		Integer	:col0
		Integer	:col1
		String :col2
		index [:col0, :col1]
	end

	DB.create_table :table_1m_noindex do
		Integer	:col0
		Integer	:col1
		String :col2
	end

	DB.create_table :table_1m_index do
		Integer	:col0
		Integer	:col1
		String :col2
		index :col0
	end

	DB.create_table :table_1m_two_index do
		Integer	:col0
		Integer	:col1
		String :col2
		index [:col0, :col1]
	end

	DB.create_table :table_10m_noindex do
		Integer	:col0
		Integer	:col1
		String :col2
	end

	DB.create_table :table_10m_index do
		Integer	:col0
		Integer	:col1
		String :col2
		index :col0
	end

	DB.create_table :table_10m_two_index do
		Integer	:col0
		Integer	:col1
		String :col2
		index [:col0, :col1]
	end
end

def generate_data()
	puts 'generate_data()'

	generate(DB[:table_100k_noindex], 100 * 1000)
	generate(DB[:table_100k_index], 100 * 1000)
	generate(DB[:table_100k_two_index], 100 * 1000)
	generate(DB[:table_1m_noindex], 1000 * 1000)
	generate(DB[:table_1m_index], 1000 * 1000)
	generate(DB[:table_1m_two_index], 1000 * 1000)
	generate(DB[:table_10m_noindex], 10000 * 1000)
	generate(DB[:table_10m_index], 10000 * 1000)
	generate(DB[:table_10m_two_index], 10000 * 1000)
end

def generate(table, count)
	DB.transaction do
		count.times{
			table.insert(:col0 => rand(2 ** 31), :col1 => rand(2 ** 31), :col2 => ('a'..'z').to_a.shuffle[0..8].join)
		}
	end
end

def benchmark()
	puts 'benchmark()'

	search(DB[:table_100k_noindex])
	search(DB[:table_100k_index])
	search(DB[:table_100k_two_index])
	search(DB[:table_1m_noindex])
	search(DB[:table_1m_index])
	search(DB[:table_1m_two_index])
	search(DB[:table_10m_noindex])
	search(DB[:table_10m_index])
	search(DB[:table_10m_two_index])
end

def search(table)
	query = table.where{col0 <= 2 ** 31 / 2}.order(:col1).limit(10000)
	puts query.sql
	bench do
		query.each{}
	end

	query = table.where{col1 <= 2 ** 31 / 2}.order(:col0).limit(10000)
	puts query.sql
	bench do
		query.each{}
	end
end

def bench(&blk)
	st = Time.now
	10.times{
		yield
	}
	ed = Time.now
	STDERR.puts ((ed - st).to_f / 10).to_s
end

DB = Sequel.sqlite('DB')
create_database()
generate_data()
benchmark()
