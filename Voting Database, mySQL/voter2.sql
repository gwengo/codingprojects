use voter_info_goins;

LOAD DATA INFILE "/Users/gwengoins/Desktop/voterINFO-01.csv" INTO TABLE voter_info COLUMNS TERMINATED BY '$';


DROP TABLE IF EXISTS voter_info;
CREATE TABLE voter_info (
  precinct_desc varchar(200) DEFAULT NULL,
  party_cd varchar(200) DEFAULT NULL,
  race_code varchar(200) DEFAULT NULL,
  ethnic_code varchar(200) DEFAULT NULL,
  sex_code varchar(200) DEFAULT NULL,
  age varchar(200) DEFAULT NULL,
  pct_portion varchar(200) DEFAULT NULL,
  first_name varchar(200) DEFAULT NULL,
  middle_name varchar(200) DEFAULT NULL,
  last_name varchar(200) DEFAULT NULL,
  name_suffix_lbl varchar(200) DEFAULT NULL,
  full_name_mail varchar(200) DEFAULT NULL,
  mail_addr1 varchar(200) DEFAULT NULL,
  mail_addr2 varchar(200) DEFAULT NULL,
  mail_addr3 varchar(200) DEFAULT NULL,
  mail_addr4 varchar(200) DEFAULT NULL,
  mail_city_state_zip varchar(200) DEFAULT NULL,
  house_num varchar(200) DEFAULT NULL,
  half_code varchar(200) DEFAULT NULL,
  street_dir varchar(200) DEFAULT NULL,
  street_name varchar(200) DEFAULT NULL,
  street_type_cd varchar(200) DEFAULT NULL,
  street_sufx_cd varchar(200) DEFAULT NULL,
  unit_designator varchar(200) DEFAULT NULL,
  unit_num varchar(200) DEFAULT NULL,
  res_city_desc varchar(200) DEFAULT NULL,
  state_cd varchar(200) DEFAULT NULL,
  zip_code varchar(200) DEFAULT NULL,
  registr_dt varchar(200) DEFAULT NULL,
  voter_reg_num varchar(200) DEFAULT NULL,
  status_cd varchar(200) DEFAULT NULL,
  municipality_desc varchar(200) DEFAULT NULL,
  ward_desc varchar(200) DEFAULT NULL,
  cong_dist_desc varchar(200) DEFAULT NULL,
  super_court_desc varchar(200) DEFAULT NULL,
  judic_dist_desc varchar(200) DEFAULT NULL,
  nc_senate_desc varchar(200) DEFAULT NULL,
  nc_house_desc varchar(200) DEFAULT NULL,
  county_commiss_desc varchar(200) DEFAULT NULL,
  school_dist_desc varchar(200) DEFAULT NULL,
  dist_1_desc varchar(200) DEFAULT NULL,
  E1 varchar(200) DEFAULT NULL,
  E1_date varchar(200) DEFAULT NULL,
  E1_VotingMethod varchar(200) DEFAULT NULL,
  E1_PartyCd varchar(200) DEFAULT NULL,
  E2 varchar(200) DEFAULT NULL,
  E2_Date varchar(200) DEFAULT NULL,
  E2_VotingMethod varchar(200) DEFAULT NULL,
  E2_PartyCd varchar(200) DEFAULT NULL,
  E3 varchar(200) DEFAULT NULL,
  E3_Date varchar(200) DEFAULT NULL,
  E3_VotingMethod varchar(200) DEFAULT NULL,
  E3_PartyCd varchar(200) DEFAULT NULL,
E4 varchar(200) DEFAULT NULL,
  E4_Date varchar(200) DEFAULT NULL,
  E4_VotingMethod varchar(200) DEFAULT NULL,
  E4_PartyCd varchar(200) DEFAULT NULL,
  E5 varchar(200) DEFAULT NULL,
  E5_Date varchar(200) DEFAULT NULL,
  E5_VotingMethod varchar(200) DEFAULT NULL,
  E5_PartyCd varchar(200) DEFAULT NULL
);


DROP TABLE IF EXISTS Voter;
CREATE TABLE IF NOT EXISTS Voter(
voter_reg_num varchar(200)  primary key,
precinct_desc  varchar(200) DEFAULT NULL,
party_cd varchar(200) DEFAULT NULL,
race_code varchar(200) DEFAULT NULL,
ethnic_code varchar(200) DEFAULT NULL,
sex_code varchar(200) DEFAULT NULL,
age varchar(200) DEFAULT NULL,
pct_portion varchar(200) DEFAULT NULL,
first_name varchar(200) DEFAULT NULL,
middle_name varchar(200) DEFAULT NULL,
last_name varchar(200) DEFAULT NULL,
name_suffix_lbl varchar(200) DEFAULT NULL,
full_name_mail varchar(200) DEFAULT NULL,
mail_addr1 varchar(200) DEFAULT NULL,
mail_addr2 varchar(200) DEFAULT NULL,
mail_addr3 varchar(200) DEFAULT NULL,
mail_addr4 varchar(200) DEFAULT NULL,
mail_city_state_zip varchar(200) DEFAULT NULL,
house_num varchar(200) DEFAULT NULL,
half_code varchar(200) DEFAULT NULL,
street_dir varchar(200) DEFAULT NULL,
street_name varchar(200) DEFAULT NULL,
street_type_cd varchar(200) DEFAULT NULL,
street_sufx_cd varchar(200) DEFAULT NULL,
unit_designator varchar(200) DEFAULT NULL,
unit_num varchar(200) DEFAULT NULL,
res_city_desc varchar(200) DEFAULT NULL,
state_cd varchar(200) DEFAULT NULL,
zip_code varchar(200) DEFAULT NULL
    );
INSERT INTO Voter 
SELECT voter_reg_num, precinct_desc , party_cd , race_code , ethnic_code , sex_code , age , pct_portion , first_name , middle_name , last_name , name_suffix_lbl , full_name_mail , mail_addr1 , mail_addr2 , mail_addr3 , mail_addr4 , mail_city_state_zip , house_num , half_code , street_dir , street_name , street_type_cd , street_sufx_cd , unit_designator , unit_num , res_city_desc , state_cd , zip_code
FROM voter_info;


DROP TABLE IF EXISTS Votes;
CREATE TABLE IF NOT EXISTS Votes(
	voter_reg_num varchar(200) primary key,
	registr_dt varchar(200) DEFAULT NULL,
  status_cd varchar(200) DEFAULT NULL,
  municipality_desc varchar(200) DEFAULT NULL,
  ward_desc varchar(200) DEFAULT NULL,
  cong_dist_desc varchar(200) DEFAULT NULL,
  super_court_desc varchar(200) DEFAULT NULL,
  judic_dist_desc varchar(200) DEFAULT NULL,
  nc_senate_desc varchar(200) DEFAULT NULL,
nc_house_desc varchar(200) DEFAULT NULL,
  county_commiss_desc varchar(200) DEFAULT NULL,
  school_dist_desc varchar(200) DEFAULT NULL,
  dist_1_desc varchar(200) DEFAULT NULL,
  FOREIGN KEY (voter_reg_num) REFERENCES Voter(voter_reg_num) ON DELETE CASCADE
    );
INSERT INTO Votes 
SELECT voter_reg_num, registr_dt  , status_cd , municipality_desc , ward_desc , cong_dist_desc , super_court_desc , judic_dist_desc , nc_senate_desc , nc_house_desc , county_commiss_desc , school_dist_desc , dist_1_desc
FROM voter_info;



DROP TABLE IF EXISTS Election;
CREATE TABLE IF NOT EXISTS Election(
	voter_reg_num varchar(200)  primary key,
    E1 varchar(200) DEFAULT NULL unique,
    E2 varchar(200) DEFAULT NULL unique,
    E3 varchar(200) DEFAULT NULL unique,
    E4 varchar(200) DEFAULT NULL unique,
    E5 varchar(200) DEFAULT NULL unique,
    FOREIGN KEY (voter_reg_num) REFERENCES Voter(voter_reg_num) ON DELETE CASCADE
    );
INSERT INTO Election 
SELECT  voter_reg_num, E1 , E2, E3, E4, E5
FROM voter_info;


DROP TABLE IF EXISTS Election1;
CREATE TABLE IF NOT EXISTS Election1(
	voter_reg_num varchar(200)  primary key NOT Null,
    E1  varchar(200)  ,
   E1_date varchar(200) DEFAULT NULL,
  E1_VotingMethod varchar(200) DEFAULT NULL,
  E1_PartyCd varchar(200) DEFAULT NULL,
   FOREIGN KEY (voter_reg_num) REFERENCES Voter(voter_reg_num) ON DELETE CASCADE
    );
INSERT INTO Election1 
SELECT  voter_reg_num, E1,  E1_date, E1_VotingMethod, E1_PartyCd
FROM voter_info
where E1_date <> "";

DROP TABLE IF EXISTS Election2;
CREATE TABLE IF NOT EXISTS Election2(
voter_reg_num varchar(200)  primary key NOT Null,
	E2  varchar(200)  ,
   E2_date varchar(200) DEFAULT NULL,
  E2_VotingMethod varchar(200) DEFAULT NULL,
  E2_PartyCd varchar(200) DEFAULT NULL,
   FOREIGN KEY (voter_reg_num) REFERENCES Voter(voter_reg_num) ON DELETE CASCADE
    );
    
    
INSERT INTO Election2 
SELECT  voter_reg_num, E2,  E2_date, E2_VotingMethod, E2_PartyCd
FROM voter_info
where E2_date <> "";


DROP TABLE IF EXISTS Election3;
CREATE TABLE IF NOT EXISTS Election3(
voter_reg_num varchar(200)  primary key NOT Null,
	E3  varchar(200) ,
   E3_date varchar(200) DEFAULT NULL,
  E3_VotingMethod varchar(200) DEFAULT NULL,
  E3_PartyCd varchar(200) DEFAULT NULL,
   FOREIGN KEY (voter_reg_num) REFERENCES Voter(voter_reg_num) ON DELETE CASCADE
    );
INSERT INTO Election3 
SELECT  voter_reg_num, E3,  E3_date, E3_VotingMethod, E3_PartyCd
FROM voter_info
where E3_date <> "";


DROP TABLE IF EXISTS Election4;
CREATE TABLE IF NOT EXISTS Election4(
voter_reg_num varchar(200)  primary key NOT Null,
	E4  varchar(200),
   E4_date varchar(200) DEFAULT NULL,
  E4_VotingMethod varchar(200) DEFAULT NULL,
  E4_PartyCd varchar(200) DEFAULT NULL,
   FOREIGN KEY (voter_reg_num) REFERENCES Voter(voter_reg_num) ON DELETE CASCADE
    );
    
INSERT INTO Election4 
SELECT  voter_reg_num, E4,  E4_date, E4_VotingMethod, E4_PartyCd
FROM voter_info
where E4_date <> "";


DROP TABLE IF EXISTS Election5;
CREATE TABLE IF NOT EXISTS Election5(
voter_reg_num varchar(200)  primary key NOT Null,
	E5  varchar(200),
   E5_date varchar(200) not null,
  E5_VotingMethod varchar(200) DEFAULT NULL,
  E5_PartyCd varchar(200) DEFAULT NULL,
   FOREIGN KEY (voter_reg_num) REFERENCES Voter(voter_reg_num) ON DELETE CASCADE
    );
    
INSERT INTO Election5 
SELECT  voter_reg_num, E5,  E5_date, E5_VotingMethod, E5_PartyCd
FROM voter_info
where E5_date <> "";


select count(*) from Election4;
select count(*) from Election5;

select count(*) from Election3;

select count(*) from Election2;

select count(*) from Election1;

select count(*) from Election;

select count(*) from Votes;

select count(*) from Voter;

