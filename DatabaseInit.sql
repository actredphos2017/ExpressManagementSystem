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

insert into orderInfo(trackNumber, company, recipentName, recipentPhoneNum, recipentLocation, recipentPost, senderName, senderPhoneNum, senderLocation, senderPost, itemWeight, pickCode) values
    ('754835986','SF','成功','19220917619','成华大道',001011,'码农','1928384019','华夏花园',495732,2.54,'23-4-5315'),
    ('645789532','YT','Jenny','19284754819','成华大道',001011,'郭华北','18573832785','叠梦礼堂',582934,7.35,'58-2-2387'),
    ('481928394','SF','万云华','19583732849','成华大道',001011,'章祥','18593829405','创维科技工业园',482948,5.41,'45-3-5719'),
    ('598169349','JD','陈海','19385738291','成华大道',001011,'Tom','12534853723','溢家商务宾馆',168394,3.52,'34-5-6931'),
    ('143392841','SF','成功','19220917619','成华大道',001011,'陈少峰','1928384019','恒隆农家饭店',495732,2.23,'31-4-4235'),
    ('534091355','SF','成功','19220917619','成华大道',001011,'包望天','14759285930','阿回百货',394529,1.53,'21-4-4362'),
    ('349239581','SF','成功','19220917619','成华大道',001011,'郭万象','15486829853','新建村文化活动中心',293185,0.41,'03-2-6345'),
    ('128378391','SF','成功','19220917619','成华大道',001011,'宋南风','18537586394','裕昌米业',234612,3.32,'42-5-4231'),
    ('309182937','SF','成功','19220917619','成华大道',001011,'张元','14850385963','大华达建材',432154,3.53,'16-1-4123'),
    ('491283748','SF','成功','19220917619','成华大道',001011,'陈方文','1867847583','林蓉工业园',348124,1.23,'04-3-4322'),
    ('439458329','SF','成功','19220917619','成华大道',001011,'华文','19284758372','松鹤山庄',591249,3.23,'06-2-5342'),
    ('539348439','SF','成功','19220917619','成华大道',001011,'迪恩斯','1482583934','鑫味园农庄',584123,2.23,'01-5-2315');