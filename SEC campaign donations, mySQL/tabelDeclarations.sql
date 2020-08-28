DROP SCHEMA IF EXISTS projectTwo;
CREATE SCHEMA projectTwo;
USE projectTwo;
-- SELECT * FROM candidateMasterFile;
-- DROP TABLE IF EXISTS candidateMaster;
CREATE TABLE candidateMaster (
    cand_id VARCHAR(9),
    cand_name VARCHAR(200),
    cand_pty_affiliation VARCHAR(3),
    cand_election_yr VARCHAR(4),
    cand_office_st VARCHAR(2), -- Candidate State
    cand_office VARCHAR(1),
    cand_office_district VARCHAR(2),
    cand_ici VARCHAR(1),
    cand_status VARCHAR(1),
    cand_pcc VARCHAR(9), -- ID of principle campaign committee
    cand_st1 VARCHAR(34),
    cand_st2 VARCHAR(34),
    cand_city VARCHAR(30),
    cand_st VARCHAR(2),
    cand_zip VARCHAR(9)
);

-- DROP TABLE IF EXISTS committeeMaster;
CREATE TABLE committeeMaster(
	cmte_id VARCHAR(9),
    cmte_nm VARCHAR(200),
    tres_nm VARCHAR(90), -- Treasurer's name
    cmte_st1 VARCHAR(34),
    cmte_st2 VARCHAR(34),
    cmte_city VARCHAR(30),
    cmte_st VARCHAR(2),
    cmte_zip VARCHAR(9),
    cmte_dsgn VARCHAR(1),
    cmte_tp VARCHAR(1),
    cmte_pty_affiliation VARCHAR(3),
    cmte_filing_freq VARCHAR(1),
    org_tp VARCHAR(1),
    connected_org_nm VARCHAR(200),
    cand_id VARCHAR(9) -- Relevent Candidate ID
);

-- DROP TABLE IF EXISTS candidateCommitteeLinkages;
CREATE TABLE candidateCommitteeLinkages(
	cand_id VARCHAR(9) NOT NULL,
    cand_election_yr INT(4) NOT NULL,
    fec_election_yr INT(4) NOT NULL,
    cmte_id VARCHAR(9),
    cmte_tp VARCHAR(1),
    cmte_dsgn VARCHAR(1),
    linkage_id INT(12) PRIMARY KEY
);

-- DROP TABLE IF EXISTS ab;
CREATE TABLE ab( -- This is the individual donations table... It's really big
	cmte_id VARCHAR(9),
    amdt_ind VARCHAR(1),
    rpt_tp VARCHAR(3),
    transaction_pgi VARCHAR(5),
    image_num VARCHAR(18),
    transaction_tp VARCHAR(3),
    entity_tp VARCHAR(3),
    name1 VARCHAR(200),
    city VARCHAR(30),
    state VARCHAR(2),
    zip_code VARCHAR(9),
    employer VARCHAR(38),
    occupation VARCHAR(38),
    transaction_dt VARCHAR(9),
    transaction_amt VARCHAR(16),
    other_id VARCHAR(9),
    tran_ID VARCHAR(32),
    file_num VARCHAR(50),
    memo_cd VARCHAR(1),
    memo_txt VARCHAR(100),
    sup_id VARCHAR(50) -- Unique row ID
);

-- DROP TABLE IF EXISTS expendatureMaster;
CREATE TABLE expendatureMaster( -- Operating Expenses
	cmte_id VARCHAR(9) NOT NULL,
    amndt_ind VARCHAR(1),
    rpt_yr VARCHAR(4),
    rpt_tp VARCHAR(3),
    image_num VARCHAR(18),
    line_num VARCHAR(20),
    form_tp_cd VARCHAR(8),
    sched_tp_cd VARCHAR(8),
    name_ VARCHAR(200),
    city VARCHAR(30),
    state VARCHAR(2),
    zip_code varchar(9),
    transaction_dt VARCHAR(10),
    transaction_amt VARCHAR(16),
    transaction_pgi VARCHAR(5),
    purpose VARCHAR(100),
    category VARCHAR(3),
    category_desc VARCHAR(40), -- dependent on category
    memo_cd VARCHAR(1),
    memo_text VARCHAR(100),
    entity_tp VARCHAR(3),
    sub_id VARCHAR(19) PRIMARY KEY,
    file_num VARCHAR(7),
    tran_id VARCHAR(32),
    back_ref_tran_id VARCHAR(32),
    blank_column VARCHAR(1)
);
    
-- This is the end of the table declarations. Next, we will normalize the tables

  
DROP TABLE IF EXISTS Candidate;
CREATE TABLE Candidate (
    cand_id VARCHAR(9) PRIMARY KEY,
    cand_name VARCHAR(200),
    party VARCHAR(3),
    cand_office_state VARCHAR(2),
    cand_office VARCHAR(1),
    cand_office_district VARCHAR(2),
    cand_ici VARCHAR(1),
    cand_status VARCHAR(1),
    st1 VARCHAR(34),
    st2 VARCHAR(34),
    city VARCHAR(30),
    st VARCHAR(2),
    zip VARCHAR(9)
);
INSERT INTO Candidate
SELECT DISTINCT (cand_id), cand_name, cand_pty_affiliation, cand_office_st, cand_office, 
cand_office_district, cand_ici,cand_status, cand_st1, cand_st2, cand_city,
cand_st, cand_zip
FROM candidateMaster;

DROP TABLE IF EXISTS Committee;
CREATE TABLE Committee(
	cmte_id VARCHAR(9) PRIMARY KEY,
    cmte_name VARCHAR(200),
    tres_name VARCHAR(90), -- Treasurer's name
    st1 VARCHAR(34),
    st2 VARCHAR(34),
    city VARCHAR(30),
    st VARCHAR(2),
    zip VARCHAR(9),
    cmte_dsgn VARCHAR(1),
    cmte_tp VARCHAR(1),
    party VARCHAR(3),
    connected_org_name VARCHAR(200));    
INSERT INTO Committee
SELECT DISTINCT(cmte_id), cmte_nm, tres_nm, cmte_st1, cmte_st2, cmte_city,
cmte_st, cmte_zip, cmte_dsgn, cmte_tp, cmte_pty_affiliation, connected_org_nm
FROM committeeMaster;

DROP TABLE IF EXISTS Connections;
CREATE TABLE Connections(
	cand_id VARCHAR(9) NOT NULL,
    cmte_id VARCHAR(9) NOT NULL,
    PRIMARY KEY(cand_id, cmte_id),
    FOREIGN KEY (cand_id)
    REFERENCES Candidate(cand_id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
    FOREIGN KEY (cmte_id)
    REFERENCES Committee(cmte_id)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);
INSERT INTO Connections
SELECT DISTINCT cand_id, cmte_id
FROM candidateCommitteeLinkages
WHERE cand_id IN (SELECT cand_id FROM Candidate) 
AND cmte_id IN (SELECT cmte_id FROM Committee);


DROP TABLE IF EXISTS Expenditure;
CREATE TABLE Expenditure(
	cmte_id VARCHAR(9) NOT NULL,
    vendor_name VARCHAR(200),
    city VARCHAR(30),
    state VARCHAR(2),
    zip_code varchar(9),
    transaction_dt VARCHAR(10),
    transaction_amt VARCHAR(16),
    transaction_pgi VARCHAR(5),
    purpose VARCHAR(100),
    category_code VARCHAR(3),
    memo_text VARCHAR(100),
    sub_id VARCHAR(19) PRIMARY KEY);
INSERT INTO Expenditure
SELECT cmte_id, name_, city, state, zip_code, transaction_dt, transaction_amt,
transaction_pgi, purpose, category, memo_text, sub_id
FROM expendatureMaster;

DROP TABLE IF EXISTS Contribution;
CREATE TABLE Contribution(
	cmte_id VARCHAR(9),
    transaction_pgi VARCHAR(5),
    contributor_name VARCHAR(200),
    city VARCHAR(30),
    state VARCHAR(2),
    zip VARCHAR(9),
    employer VARCHAR(38),
    occupation VARCHAR(38),
    transaction_dt VARCHAR(9),
    transaction_amt VARCHAR(16),
    memo_txt VARCHAR(100),
    sup_id VARCHAR(50)); -- Unique row ID
INSERT INTO Contribution
SELECT cmte_id, transaction_pgi, name1, city, state, zip_code, employer,
occupation, transaction_dt, transaction_amt, memo_txt,sup_id
FROM ab;

DROP TRIGGER IF EXISTS donationLimit;
DELIMITER //
CREATE TRIGGER donationLimit -- Federal law prohibits donations greater than $2,700
BEFORE INSERT
ON Contribution
FOR EACH ROW
IF CAST(NEW.transaction_amt AS DECIMAL) > (2700*2) THEN
SET NEW.transaction_amt = '5400'; -- We use $5,400 because you can donate twice: primary and general
ELSEIF CAST(NEW.transaction_amt AS DECIMAL) < (0) THEN
SET NEW.transaction_amt = '0';
END IF;

//
DELIMITER ;

DROP TABLE IF EXISTS Disbursement_Category;
CREATE TABLE Disbursement_Category(
	category_code VARCHAR(3) PRIMARY KEY,
    description VARCHAR(400));
INSERT INTO Disbursement_Category (category_code, description) VALUES
 ('001', 'Administrative/salary/overhead expenses (e.g., rent, staff salaries, postage, office supplies, equipment, furniture, ballot access fees, petition drives, party fees and legal and accounting expenses)'),
 ('002', 'Travel expenses - including travel reimbursement expenses (e.g., costs of commercial carrier tickets; reimbursements for use of private vehicles, advance payments for use of corporate aircraft; lodging and meal expenses incurred during travel)'),
 ('003', 'Solicitation and fundraising expenses (e.g., costs for direct mail solicitations and fundraising events including printing, mailing lists, consultant fees, call lists, invitations, catering costs and room rental)'),
 ('004', 'Advertising expenses -including general public political advertising (e.g., purchases of radio/television broadcast/cable time, print advertisements and related production costs)'),
 ('005', 'Polling expenses'),
 ('006', 'Campaign materials (e.g., buttons, bumper stickers, brochures, mass mailings, pens, posters, balloons)'),
 ('007', 'Campaign event expenses (e.g., costs associated with candidate appearances, campaign rallies, town meetings, phone banks, including catering costs, door to door get-out-the-vote efforts and driving voters to the polls)'),
 ('008', 'Transfers (e.g., to other authorized committees of the same candidate)'),
 ('009', 'Loan repayments (e.g., repayments of loans made/guaranteed by the candidate or other person)'),
 ('010', 'Refunds of contributions (e.g., contribution refunds to individuals/ persons, political party committees or other political committees)'),
 ('011', 'Political contributions (e.g., contributions to other federal candidates and committees, donations to nonfederal candidates and committees)'),
 ('012', 'Donations (e.g., donations to charitable or civic organizations'),
 ('102', 'Media expenditures'),
 ('103', 'Expenditures for mass mailings and other campaign materials (e.g., buttons, bumper stickers, brochures, mass mailings, pens, posters, balloons)'),
 ('104', 'Overhead expenditures of state offices and their facilities (e.g., rent, staff salaries, postage, office supplies, equipment, furniture, ballot access fees, petition drives, party fees and legal and accounting expenses)'),
 ('105', 'Expenditures for special telephone programs'),
 ('106', 'Public opinion poll expenditures'),
 ('107', 'Fundraising expenditures (e.g., costs for direct mail solicitations & fundraising events including printing, mailing lists, consultant fees, call lists, invitations, catering costs and room rental)');

DROP TABLE IF EXISTS Party;
CREATE TABLE Party(
	pty_code VARCHAR(3) PRIMARY KEY,
    pty_name VARCHAR(100));
INSERT INTO Party (pty_code, pty_name) VALUES
	 ('ACE', 'Ace Party'),
	 ('AKI', 'Alaskan Independence Party'),
	 ('AIC', 'American Independent Conservative'),
	 ('AIP', 'American Independent Party'),
	 ('AMP', 'American Party'),
	 ('APF', 'American People\'s Freedom Party'),
	 ('AE', 'Americans Elect'),
	 ('CIT', 'Citizens\' Party'),
	 ('CMD', 'Commandments Party'),
	 ('CMP', 'Commonwealth Party of the U.S.'),
	 ('COM', 'Communist Party'),
	 ('CNC', 'Concerned Citizens Party Of Connecticut'),
	 ('CRV', 'Conservative Party'),
	 ('CON', 'Constitution Party'),
	 ('CST', 'Constitutional'),
	 ('COU', 'Country'),
	 ('DCG', 'D.C. Statehood Green Party'),
	 ('DNL', 'Democratic -Nonpartisan League'),
	 ('DEM', 'Democratic Party'),
	 ('D/C', 'Democratic/Conservative'),
	 ('DFL', 'Democratic-Farmer-Labor'),
	 ('DGR', 'Desert Green Party'),
	 ('FED', 'Federalist'),
	 ('FLP', 'Freedom Labor Party'),
	 ('FRE', 'Freedom Party'),
	 ('GWP', 'George Wallace Party'),
	 ('GRT', 'Grassroots'),
	 ('GRE', 'Green Party'),
	 ('GR', 'Green-Rainbow'),
	 ('HRP', 'Human Rights Party'),
	 ('IDP', 'Independence Party'),
	 ('IND', 'Independent'),
	 ('IAP', 'Independent American Party'),
	 ('ICD', 'Independent Conservative Democratic'),
	 ('IGR', 'Independent Green'),
	 ('IP', 'Independent Party'),
	 ('IDE', 'Independent Party of Delaware'),
	 ('IGD', 'Industrial Government Party'),
	 ('JCN', 'Jewish/Christian National'),
	 ('JUS', 'Justice Party'),
	 ('LRU', 'La Raza Unida'),
	 ('LBR', 'Labor Party'),
	 ('LFT', 'Less Federal Taxes'),
	 ('LBL', 'Liberal Party'),
	 ('LIB', 'Libertarian Party'),
	 ('LBU', 'Liberty Union Party'),
	 ('MTP', 'Mountain Party'),
	 ('NDP', 'National Democratic Party'),
	 ('NLP', 'Natural Law Party'),
	 ('NA', 'New Alliance'),
	 ('NJC', 'New Jersey Conservative Party'),
	 ('NPP', 'New Progressive Party'),
	 ('NPA', 'No Party Affiliation'),
	 ('NOP', 'No Party Preference'),
	 ('NNE', 'None'),
	 ('N', 'Nonpartisan'),
	 ('NON', 'Non-Party'),
	 ('OE', 'One Earth Party'),
	 ('OTH', 'Other'),
	 ('PG', 'Pacific Green'),
	 ('PSL', 'Party for Socialism and Liberation'),
	 ('PAF', 'Peace And Freedom'),
	 ('PFP', 'Peace And Freedom Party'),
	 ('PFD', 'Peace Freedom Party'),
	 ('POP', 'People Over Politics'),
	 ('PPY', 'People\'s Party'),
	 ('PCH', 'Personal Choice Party'),
	 ('PPD', 'Popular Democratic Party'),
	 ('PRO', 'Progressive Party'),
	 ('NAP', 'Prohibition Party'),
	 ('PRI', 'Puerto Rican Independence Party'),
	 ('RUP', 'Raza Unida Party'),
	 ('REF', 'Reform Party'),
	 ('REP', 'Republican Party'),
	 ('RES', 'Resource Party'),
	 ('RTL', 'Right To Life'),
	 ('SEP', 'Socialist Equality Party'),
	 ('SLP', 'Socialist Labor Party'),
	 ('SUS', 'Socialist Party'),
	 ('SOC', 'Socialist Party U.S.A.'),
	 ('SWP', 'Socialist Workers Party'),
	 ('TX', 'Taxpayers'),
	 ('TWR', 'Taxpayers Without Representation'),
	 ('TEA', 'Tea Party'),
	 ('THD', 'Theo-Democratic'),
	 ('LAB', 'U.S. Labor Party'),
	 ('USP', 'U.S. People\'s Party'),
	 ('UST', 'U.S. Taxpayers Party'),
	 ('UN', 'Unaffiliated'),
	 ('UC', 'United Citizen'),
	 ('UNI', 'United Party'),
	 ('UNK', 'Unknown'),
	 ('VET', 'Veterans Party'),
	 ('WTP', 'We the People'),
	 ('W', 'Write-In');

DROP TABLE IF EXISTS committee_type;
CREATE TABLE committee_type(
	cmte_tp_code VARCHAR(1) PRIMARY KEY,
    cmte_tp_name VARCHAR(100),
    cmte_tp_expln VARCHAR(400));
INSERT INTO committee_type (cmte_tp_code, cmte_tp_name, cmte_tp_expln) VALUES
	 ('C', 'Communication cost', 'Organizations like corporations or unions may prepare communications for their employees or members that advocate the election of specific candidates and they must disclose them under certain circumstances. These are usually paid with direct corporate or union funds rather than from PACs.'),
	 ('D', 'Delegate committee', 'Delegate committees are organized for the purpose of influencing the selection of delegates to Presidential nominating conventions. The term includes a group of delegates, a group of individuals seeking to become delegates, and a group of individuals supporting delegates.'),
	 ('E', 'Electioneering communication', 'Groups (other than PACs) making electioneering communications'),
	 ('H', 'House', 'Campaign committees for candidates for the U.S. House of Representatives'),
	 ('I', 'Independent expenditor (person or group)', 'Individuals or groups (other than PACs) making independent expenditures over $250 in a year must disclose those expenditures'),
	 ('N', 'PAC - nonqualified', 'PACs that have not yet been in existence for six months and received contributions from 50 people and made contributions to five federal candidates. These committees have lower limits for their contributions to candidates.'),
	 ('O', 'Independent expenditure-only (Super PACs)', 'Political Committee that has filed a statement consistent with AO 2010-09 or AO 2010-11.'),
	 ('P', 'Presidential', 'Campaign committee for candidate for U.S. President'),
	 ('Q', 'PAC - qualified', 'PACs that have been in existence for six months and received contributions from 50 people and made contributions to five federal candidates'),
	 ('S', 'Senate', 'Campaign committee for candidate for Senate'),
	 ('U', 'Single-candidate independent expenditure', ''),
	 ('V', 'PAC with non-contribution account - nonqualified', 'Political committees with non-contribution accounts'),
	 ('W', 'PAC with non-contribution account - qaualified', 'Political committees with non-contribution accounts'),
	 ('X', 'Party - nonqualified', 'Party committees that have not yet been in existence for six months and received contributions from 50 people, unless they are affiliated with another party committee that has met these requirements.'),
	 ('Y', 'Party - qualified', 'Party committees that have existed for at least six months and received contributions from 50 people or are affiliated with another party committee that meets these requirements.'),
	 ('Z', 'National party nonfederal account', 'National party nonfederal accounts. Not permitted after enactment of Bipartisan Campaign Reform Act of 2002.');
DROP TABLE IF EXISTS cmte_designation;
CREATE TABLE cmte_designation(
	cmte_dsgn_code VARCHAR(1),
    cmte_dsgn VARCHAR(50)
);
INSERT INTO cmte_designation (cmte_dsgn_code, cmte_dsgn) VALUES
	 ('A', 'Authorized by a candidate'),
     ('B', 'Lobbyist/Registrant PAC'),
	 ('D', 'Leadership PAC'),
	 ('J', 'Joint fundraiser'),
	 ('P', 'Principal campaign committee of a candidate'),
	 ('U', 'Unauthorized');
	
DROP TABLE IF EXISTS interest_organization_category;
CREATE TABLE interest_organization_category(
	org_tp_code VARCHAR(1) PRIMARY KEY,
    org_tp_name VARCHAR(50)
);
INSERT INTO interest_organization_category (org_tp_code, org_tp_name) VALUES
	 ('C', 'Corporation'),
     ('L', 'Labor organization'),
	 ('M', 'Membership organization'),
	 ('T', 'Trade association'),
	 ('V', 'Cooperative'),
	 ('W', 'Corporation without capital stock');

-- States with the most candidates running
SELECT Candidate.st AS 'State', COUNT(Candidate.st) AS 'Number of Candidates'
FROM Candidate
GROUP BY Candidate.st
ORDER BY COUNT(Candidate.st) DESC
LIMIT 3;

-- Top three parties with the most people running
SELECT pty_name AS 'Party', COUNT(pty_name) AS 'Number of Candidates'
FROM Candidate JOIN Party ON Candidate.party = Party.pty_code
GROUP BY pty_name
ORDER BY COUNT(pty_name) DESC
LIMIT 3;
-- Select candidates who have raised the most CASH $$$
SELECT cand_name AS 'Candidate',
SUM(CAST(transaction_amt AS DECIMAL)) AS 'Dollers Raised'
FROM Contribution LEFT JOIN Committee USING(cmte_id) 
JOIN Connections USING (cmte_id)
JOIN Candidate USING (cand_id)
GROUP BY cand_id
ORDER BY SUM(CAST(transaction_amt AS DECIMAL)) DESC
LIMIT 3;

-- View exclusively for the Trump Capgaing. They can see their committee's expenses and income,
-- But no one elses'
CREATE OR REPLACE VIEW trumpView AS
SELECT cand_id, cand_name, Candidate.party AS 'Candidate Party', cand_office_state, cand_office, cand_office_district, cand_ici, cand_status, Candidate.st1 AS 'Candidate Street1', Candidate.st2 AS 'Candidate Street2', Candidate.city AS 'Candidate City', Candidate.st AS 'Candidate State', Candidate.zip AS 'Candidate Zip', cmte_id, cmte_name, tres_name, Committee.st1 AS 'Committee Street1', Committee.st2 AS 'Committee Street2', Committee.city AS 'Committee City', Committee.st AS 'Committee ST', Committee.zip AS 'Committee ZIP', cmte_dsgn, cmte_tp, Committee.party AS 'Committee Party', connected_org_name, pty_code, pty_name, vendor_name, Expenditure.city AS 'Expenditure city', Expenditure.state, Expenditure.zip_code, Expenditure.transaction_dt AS 'Expenditure Transaction Date', Expenditure.transaction_amt AS 'Expenditure Transaction Amount', Expenditure.transaction_pgi  AS 'Expenditure Transaction pgi', purpose, category_code, memo_text,  sub_id, description, Contribution.transaction_pgi AS 'Contribution Transaction pgi', contributor_name, Contribution.city AS 'Contribution city', Contribution.state AS 'Contribution state', Contribution.zip AS 'Contribution zip', employer, occupation, Contribution.transaction_dt AS 'Contribution Transaction Date', Contribution.transaction_amt AS 'Contribution Transaction Amount', memo_txt, sup_id
FROM Candidate JOIN Connections USING (cand_id)
JOIN Committee USING (cmte_id)
JOIN Party ON Candidate.party = Party.pty_code
JOIN Expenditure USING (cmte_id)
JOIN DISBURSEMENT_CATEGORY USING (category_code)
JOIN Contribution USING (cmte_id)
WHERE cand_id = 'P80001571';
    
    