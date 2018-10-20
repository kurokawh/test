# coding: utf-8
require "active_record"

# データベースへの接続
ActiveRecord::Base.establish_connection(
  adapter:   'sqlite3',
  database:  ':memory:'
)

# スキーマの設定
class InitialSchema < ActiveRecord::Migration[5.1]
  def self.up
    create_table :users do |t|
      t.string :name
      t.string :email
    end
  end

  def self.down
    drop_table :users
  end
end

# マイグレーション
InitialSchema.migrate(:up)

class User < ActiveRecord::Base
end

# モデルを生成
User.create(name: 'hogehoge')

# 表示
p User.all


# my test code ===>
u2 = User.new({name: 'abc'})
u2.name = 'abc2'
p u2.name
u2.save

p User.all

p u2
p u2.name
u2.name = 'xyg'
u2.save
p User.all

# <===



# how to setup:
# 
# % gem install activerecord
# % gem install sqlite3
# % gem install bigdecimal
# % gem install json
#
# refer:
#   https://qiita.com/xkumiyu/items/2ecee242b7e6e6c6d9a1
#   https://qiita.com/kimioka0/items/8c10e01def23fdbf3aa6
