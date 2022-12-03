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
    company varchar(10) not null,
    recipentName varchar(10) not null,
    recipentPhoneNum varchar(15) not null,
    recipentLocation varchar(15) not null,
    recipentPost int,
    senderName varchar(10) not null,
    senderPhoneNum varchar(15) not null,
    senderLocation varchar(15) not null,
    senderPost int,
    itemWeight float,
    pickCode varchar(10),
    warehousingTime datetime default now(),
    hasBeenTaken boolean default true,
    primary key(trackNumber),
    index(pickCode)
)engine=InnoDB, charset=utf8;