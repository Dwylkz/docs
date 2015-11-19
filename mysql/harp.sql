create table if not exists harp
(
  id int(32) unsigned auto_increment,
  mainkey varchar(128) not null,
  brand varchar(128) not null,
  product varchar(128) not null,
  rmb float not null,
  primary key (id)
) engine=innodb, default charset=utf8;
