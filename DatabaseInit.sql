drop database if exists ExpressManagementSystem;
create database ExpressManagementSystem;
use ExpressManagementSystem;

drop table if exists account;
create table account(
    isWaiter boolean default false,
    userName varchar(15) default null,
    phoneNumber varchar(15) default null,
    password varchar(20) not null,
    permissionCode char(32) default md5(now()),
    primary key(userName, phoneNumber)
)engine=InnoDB, charset=utf8;

insert into account (isWaiter, userName, phoneNumber, password) values (1, 'root', '', 'helloworld');

drop table if exists orderInfo;
create table orderInfo(
    trackNumber varchar(20) not null,
    company varchar(10) default null,
    recipentName varchar(10) not null,
    recipentPhoneNum varchar(15) default null,
    recipentLocation varchar(15) default null,
    recipentPost int default 0,
    senderName varchar(10) not null,
    senderPhoneNum varchar(15) default null,
    senderLocation varchar(15) default null,
    senderPost int default 0,
    itemWeight float default 1.0,
    pickCode varchar(10),
    warehousingTime datetime default now(),
    hasBeenTaken boolean default false,
    primary key(trackNumber),
    index(pickCode)
)engine=InnoDB, charset=utf8;