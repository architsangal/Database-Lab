create database IMT2019012_companydb;
use IMT2019012_companydb;

create table employee
(
    fname VARCHAR(100) NOT NULL,
    minit CHAR(1),
    lname VARCHAR(100),
    ssn CHAR(9) NOT NULL,
    bdate DATE,
    var_address VARCHAR(200),
    sex CHAR(1),
    salary INT,
    super_ssn CHAR(9),
    dno INT,
    CONSTRAINT pk_employee PRIMARY KEY (ssn)
);

create table department
(
    dname VARCHAR(100) NOT NULL,
    dnumber INT NOT NULL,
    mgr_ssn CHAR(9),
    mgr_start_date DATE,
    CONSTRAINT pk_department PRIMARY KEY (dnumber)
);

create table dept_locations
(
    dnumber INT NOT NULL,
    dlocation VARCHAR(200) NOT NULL,
    CONSTRAINT pk_dept_locations PRIMARY KEY (dnumber, dlocation)
);

create table works_on
(
    essn CHAR(9) NOT NULL,
    pno INT NOT NULL,
    hrs FLOAT,
    CONSTRAINT pk_works_on PRIMARY KEY (essn, pno)
);

create table project
(
    pname VARCHAR(100),
    pnumber INT NOT NULL,
    plocation VARCHAR(100),
    dnum INT,
    CONSTRAINT pk_project PRIMARY KEY (pnumber)
);

create table table_dependent
(
    essn CHAR(9) NOT NULL,
    dependent_name VARCHAR(100) NOT NULL,
    sex CHAR(1),
    bdate DATE,
    relationship VARCHAR(100),
    CONSTRAINT pk_table_dependent PRIMARY KEY (essn, dependent_name)
);