#!/bin/bash
mysql -udwylkz -pdwylkz== -Ddwylkz<<^_^

create table if not exists test (
	id integer(20) primary key auto_increment,
	score integer(20)
);

show create table test;

delimiter //
create procedure p1()
begin
	insert into test (score) values (100);
	update test set score=score+1 where score=100;
end;

create procedure p2()
begin
	insert into test (score) values (102);
	update test set score=score+1 where score=102;
end;
//

^_^
