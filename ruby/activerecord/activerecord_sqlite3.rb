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
u2.name = 'abc2' # name can be referred & changed before storing to DB.
p u2.name
u2.save

p User.all

p u2
p u2.name
u2.name = 'xyg' # name can be changed after storing to DB.
u2.save
p User.all


u3 = User.all.first(1)[0]
p u3
u3.name = 'new-name' # replace name on memory
u3.save
p User.all
# <===



# how to setup:
# 
# % gem install activerecord
# % gem install sqlite3
# % gem install bigdecimal
# % gem install json
#
# note:
#   ruby-devel package is required to gem install sqlite3
#
# refer:
#   https://qiita.com/xkumiyu/items/2ecee242b7e6e6c6d9a1
#   https://qiita.com/kimioka0/items/8c10e01def23fdbf3aa6
