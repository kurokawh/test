create table user(name text, address text);
insert into user values('Yamada', 'Tokyo');
insert into user values('Ｙａｍａｄａ', 'Ｔｏｋｙｏ');
insert into user values('a b c', 'ｱ ｲ ｳ');
insert into user values('ABC', 'ｱｲｳ');
insert into user values('A B C', 'ｱ ｲ ｳ');
insert into user values('ＡＢＣ', 'アイウ');
insert into user values('Ａ Ｂ Ｃ', 'ア イ ウ');
insert into user values('Ａ　Ｂ　Ｃ', 'ア　イ　ウ');
--insert into user values('', '');
--insert into user values('', '');
--insert into user values('', '');
--insert into user values('', '');


select * from user;
select name as 'name:a%' from user where name like 'a%';
select name as 'name:Ａ%' from user where name like 'Ａ%';
select name as 'name:Ａ_Ｂ' from user where name like 'Ａ_Ｂ';
select name as 'name:a_b' from user where name like 'a_b';
select name as 'name:%b%' from user where name like '%b%';
select name as 'name:%Ｂ%' from user where name like '%Ｂ%';
