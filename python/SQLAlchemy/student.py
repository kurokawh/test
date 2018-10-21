#!/usr/bin/env python
# -*- coding: utf-8 -*-

# https://it-engineer-lab.com/archives/1183

##########################################################

from sqlalchemy import create_engine, Column, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
from sqlalchemy.orm.exc import NoResultFound

##########################################################

# SQLite 使用時
# SQLite - File（通常のファイル保存）
engine = create_engine('sqlite:///sample_db.sqlite3')  # スラッシュは3本
 
# SQLログを表示したい場合には echo=True を指定
engine = create_engine('sqlite:///sample_db.sqlite3', echo=True)

##########################################################
	
# モデルの作成
# 説明のためファイル内に定義しますが、実際は別ファイル化して import します。
 
# まずベースモデルを生成します
Base = declarative_base()
 
 
# 次にベースモデルを継承してモデルクラスを定義します
class Student(Base):
    """
    生徒モデル
    必ず Base を継承
    """
    __tablename__ = 'students'
 
    id = Column(Integer, primary_key=True)
    name = Column(String(255))
    score = Column(Integer)  # 点数
 
    def __repr__(self):
        return "<Student(id='%s', name='%s', score='%s')>" % (self.id, self.name, self.score)
 
 
# テーブルの作成
# テーブルがない場合 CREATE TABLE 文が実行される
Base.metadata.create_all(engine)  # 作成した engine を引数にすること

##########################################################

# SQLAlchemy はセッションを介してクエリを実行する
Session = sessionmaker(bind=engine)
session = Session()

##########################################################
# 1レコードの追加
session.add(Student(id=1, name='Suzuki', score=70))
 
# コミット（データ追加を実行）
session.commit()

##########################################################
# 複数レコードの追加
session.add_all([
    Student(id=5, name='Yamada', score=73),
    Student(id=7, name='Watanabe', score=88),
    Student(id=10, name='Tanaka', score=65),
])
 
# コミット（データ追加を実行）
session.commit()

##########################################################

student = session.query(Student).filter_by(name='Tanaka').one()
student.score = 75
session.add(student)
 
# コミット（変更を実行）
session.commit()
 
# 変更されたかを確認
student = session.query(Student).filter_by(name='Tanaka').one()
print(student)  # <Student(id='10', name='Tanaka', score='75')>

##########################################################
# mycode 

s = Student(id=20, name='Test', score=22)
print(s.name)
print(s.score)

