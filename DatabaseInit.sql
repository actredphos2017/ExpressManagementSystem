drop database if exists ExpressManagementSystem;
create database ExpressManagementSystem;
use ExpressManagementSystem;

drop table if exists account;
create table account(
    accountType enum('customer','waiter') default 'customer',
    userName varchar(15) default null,
    phoneNumber varchar(15) not null,
    password varchar(20) not null,
    primary key(userName, phoneNumber)
)engine=InnoDB, charset=utf8;

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
    hasBeenTaken boolean default true,
    primary key(trackNumber),
    index(pickCode)
)engine=InnoDB, charset=utf8;