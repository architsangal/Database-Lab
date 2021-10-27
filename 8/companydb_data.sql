-- Data of employee

insert into employee(fname, minit, lname, ssn, bdate, var_address,sex, salary, super_ssn, dno)
VALUES('John','B','Smith','123456789','1965-01-09','731, Fondren, Houston, TX','M',30000,NULL,NULL);

insert into employee(fname, minit, lname, ssn, bdate, var_address,sex, salary, super_ssn, dno)
VALUES('Franklin', 'T', 'Wong', '333445555', '1955-12-08', '638 Voss, Houston, TX', 'M', 40000, NULL, NULL);

insert into employee(fname, minit, lname, ssn, bdate, var_address,sex, salary, super_ssn, dno)
VALUES('Alicia', 'J', 'Zelaya', '999887777', '1968-01-19', '3321 Castle, Spring, TX', 'F', 25000, NULL, NULL);

insert into employee(fname, minit, lname, ssn, bdate, var_address,sex, salary, super_ssn, dno)
VALUES('Jennifer', 'S', 'Wallace', '987654321', '1941-06-20', '291 Berry, Bellaire, TX', 'F', 43000, NULL, NULL);

insert into employee(fname, minit, lname, ssn, bdate, var_address,sex, salary, super_ssn, dno)
VALUES('Ramesh', 'K', 'Narayan', '666884444', '1962-09-15', '975 Fire Oak, Humble, TX', 'M', 38000, NULL, NULL);

insert into employee(fname, minit, lname, ssn, bdate, var_address,sex, salary, super_ssn, dno)
VALUES('Joyce', 'A', 'English', '453453453', '1972-07-31', '5631 Rice, Houston, TX', 'F', 25000, NULL, NULL);

insert into employee(fname, minit, lname, ssn, bdate, var_address,sex, salary, super_ssn, dno)
VALUES('Ahmad', 'V', 'Jabbar', '987987987', '1969-03-29', '980 Dallas, Houston, TX', 'M', 25000, NULL, NULL);

insert into employee(fname, minit, lname, ssn, bdate, var_address,sex, salary, super_ssn, dno)
VALUES('James', 'E', 'Borg', '888665555', '1937-11-10', '450 Stone, Houston, TX', 'M', 55000, NULL, NULL);


-- Data of department

insert into department(dname, dnumber, mgr_ssn, mgr_start_date)
VALUES('Research', 5, '333445555', '1988-05-22');

insert into department(dname, dnumber, mgr_ssn, mgr_start_date)
VALUES('Administration', 4, '987654321', '1995-01-01');

insert into department(dname, dnumber, mgr_ssn, mgr_start_date)
VALUES('Headquarters', 1, '888665555', '1981-06-19');


-- Data of dept_locations

insert into dept_locations(dnumber,dlocation)
VALUES(1, 'Houston');

insert into dept_locations(dnumber,dlocation)
VALUES(4, 'Stafford');

insert into dept_locations(dnumber,dlocation)
VALUES(5, 'Bellaire');

insert into dept_locations(dnumber,dlocation)
VALUES(5, 'Sugarland');

insert into dept_locations(dnumber,dlocation)
VALUES(5, 'Houston');


-- Data of project

insert into project(pname,pnumber,plocation,dnum)
VALUES('ProductX', 1, 'Bellaire', 5);

insert into project(pname,pnumber,plocation,dnum)
VALUES('ProductY', 2, 'Sugarland', 5);

insert into project(pname,pnumber,plocation,dnum)
VALUES('ProductZ', 3, 'Houston', 5);

insert into project(pname,pnumber,plocation,dnum)
VALUES('Computerization', 10, 'Stafford', 4);

insert into project(pname,pnumber,plocation,dnum)
VALUES('Reorganization', 20, 'Houston', 1);

insert into project(pname,pnumber,plocation,dnum)
VALUES('Newbenefits', 30, 'Stafford', 4);


-- Data of works_on

insert into works_on(essn,pno,hrs)
VALUES('123456789', 1, 32.5);

insert into works_on(essn,pno,hrs)
VALUES('123456789', 2, 7.5);

insert into works_on(essn,pno,hrs)
VALUES('666884444', 3, 40.0);

insert into works_on(essn,pno,hrs)
VALUES('453453453', 1, 20.0);

insert into works_on(essn,pno,hrs)
VALUES('453453453', 2, 20.0);

insert into works_on(essn,pno,hrs)
VALUES('333445555', 2, 10.0);

insert into works_on(essn,pno,hrs)
VALUES('333445555', 3, 10.0);

insert into works_on(essn,pno,hrs)
VALUES('333445555', 10, 10.0);

insert into works_on(essn,pno,hrs)
VALUES('333445555', 20, 10.0);

insert into works_on(essn,pno,hrs)
VALUES('999887777', 30, 30.0);

insert into works_on(essn,pno,hrs)
VALUES('999887777', 10, 10.0);

insert into works_on(essn,pno,hrs)
VALUES('987987987', 10, 35.0);

insert into works_on(essn,pno,hrs)
VALUES('987987987', 30, 5.0);

insert into works_on(essn,pno,hrs)
VALUES('987654321', 30, 20.0);

insert into works_on(essn,pno,hrs)
VALUES('987654321', 20, 15.0);

insert into works_on(essn,pno,hrs)
VALUES('888665555', 20, NULL);


-- Data of table_dependent

insert into table_dependent(essn,dependent_name,sex,bdate,relationship)
VALUES('333445555', 'Alice', 'F', '1986-04-05', 'Daughter');

insert into table_dependent(essn,dependent_name,sex,bdate,relationship)
VALUES('333445555', 'Theodore', 'M', '1983-10-25', 'Son');

insert into table_dependent(essn,dependent_name,sex,bdate,relationship)
VALUES('333445555', 'Joy', 'F', '1958-05-03', 'Spouse');

insert into table_dependent(essn,dependent_name,sex,bdate,relationship)
VALUES('987654321', 'Abner', 'M', '1942-02-28', 'Spouse');

insert into table_dependent(essn,dependent_name,sex,bdate,relationship)
VALUES('123456789', 'Michael', 'M', '1988-01-04', 'Son');

insert into table_dependent(essn,dependent_name,sex,bdate,relationship)
VALUES('123456789', 'Alice', 'F', '1988-12-30', 'Daughter');

insert into table_dependent(essn,dependent_name,sex,bdate,relationship)
VALUES('123456789', 'Elizabeth', 'F', '1967-05-05', 'Spouse');


-- Dealing with NULL values of employee

update employee SET super_ssn = '333445555', Dno=5 WHERE ssn='123456789';

update employee SET super_ssn = '888665555', Dno=5 WHERE ssn='333445555';

update employee SET super_ssn = '987654321', Dno=4 WHERE ssn='999887777';

update employee SET super_ssn = '888665555', Dno=4 WHERE ssn='987654321';

update employee SET super_ssn = '333445555', Dno=5 WHERE ssn='666884444';

update employee SET super_ssn = '333445555', Dno=5 WHERE ssn='453453453';

update employee SET super_ssn = '987654321', Dno=4 WHERE ssn='987987987';

update employee SET Dno=1 WHERE ssn='888665555'; -- other value is NULL already

-- select * from employee;
-- select * from department;
-- select * from dept_locations;
-- select * from works_on;
-- select * from project;
-- select * from table_dependent;

-- +----------+-------+---------+-----------+------------+---------------------------+------+--------+-----------+------+
-- | fname    | minit | lname   | ssn       | bdate      | var_address               | sex  | salary | super_ssn | dno  |
-- +----------+-------+---------+-----------+------------+---------------------------+------+--------+-----------+------+
-- | John     | B     | Smith   | 123456789 | 1965-01-09 | 731, Fondren, Houston, TX | M    |  30000 | 333445555 |    5 |
-- | Franklin | T     | Wong    | 333445555 | 1955-12-08 | 638 Voss, Houston, TX     | M    |  40000 | 888665555 |    5 |
-- | Joyce    | A     | English | 453453453 | 1972-07-31 | 5631 Rice, Houston, TX    | F    |  25000 | 333445555 |    5 |
-- | Ramesh   | K     | Narayan | 666884444 | 1962-09-15 | 975 Fire Oak, Humble, TX  | M    |  38000 | 333445555 |    5 |
-- | James    | E     | Borg    | 888665555 | 1937-11-10 | 450 Stone, Houston, TX    | M    |  55000 | NULL      |    1 |
-- | Jennifer | S     | Wallace | 987654321 | 1941-06-20 | 291 Berry, Bellaire, TX   | F    |  43000 | 888665555 |    4 |
-- | Ahmad    | V     | Jabbar  | 987987987 | 1969-03-29 | 980 Dallas, Houston, TX   | M    |  25000 | 987654321 |    4 |
-- | Alicia   | J     | Zelaya  | 999887777 | 1968-01-19 | 3321 Castle, Spring, TX   | F    |  25000 | 987654321 |    4 |
-- +----------+-------+---------+-----------+------------+---------------------------+------+--------+-----------+------+
-- 8 rows in set (0.00 sec)

-- +----------------+---------+-----------+----------------+
-- | dname          | dnumber | mgr_ssn   | mgr_start_date |
-- +----------------+---------+-----------+----------------+
-- | Headquarters   |       1 | 888665555 | 1981-06-19     |
-- | Administration |       4 | 987654321 | 1995-01-01     |
-- | Research       |       5 | 333445555 | 1988-05-22     |
-- +----------------+---------+-----------+----------------+
-- 3 rows in set (0.00 sec)

-- +---------+-----------+
-- | dnumber | dlocation |
-- +---------+-----------+
-- |       1 | Houston   |
-- |       4 | Stafford  |
-- |       5 | Bellaire  |
-- |       5 | Houston   |
-- |       5 | Sugarland |
-- +---------+-----------+
-- 5 rows in set (0.00 sec)

-- +-----------+-----+------+
-- | essn      | pno | hrs  |
-- +-----------+-----+------+
-- | 123456789 |   1 | 32.5 |
-- | 123456789 |   2 |  7.5 |
-- | 333445555 |   2 |   10 |
-- | 333445555 |   3 |   10 |
-- | 333445555 |  10 |   10 |
-- | 333445555 |  20 |   10 |
-- | 453453453 |   1 |   20 |
-- | 453453453 |   2 |   20 |
-- | 666884444 |   3 |   40 |
-- | 888665555 |  20 | NULL |
-- | 987654321 |  20 |   15 |
-- | 987654321 |  30 |   20 |
-- | 987987987 |  10 |   35 |
-- | 987987987 |  30 |    5 |
-- | 999887777 |  10 |   10 |
-- | 999887777 |  30 |   30 |
-- +-----------+-----+------+
-- 16 rows in set (0.00 sec)

-- +-----------------+---------+-----------+------+
-- | pname           | pnumber | plocation | dnum |
-- +-----------------+---------+-----------+------+
-- | ProductX        |       1 | Bellaire  |    5 |
-- | ProductY        |       2 | Sugarland |    5 |
-- | ProductZ        |       3 | Houston   |    5 |
-- | Computerization |      10 | Stafford  |    4 |
-- | Reorganization  |      20 | Houston   |    1 |
-- | Newbenefits     |      30 | Stafford  |    4 |
-- +-----------------+---------+-----------+------+
-- 6 rows in set (0.00 sec)

-- +-----------+----------------+------+------------+--------------+
-- | essn      | dependent_name | sex  | bdate      | relationship |
-- +-----------+----------------+------+------------+--------------+
-- | 123456789 | Alice          | F    | 1988-12-30 | Daughter     |
-- | 123456789 | Elizabeth      | F    | 1967-05-05 | Spouse       |
-- | 123456789 | Michael        | M    | 1988-01-04 | Son          |
-- | 333445555 | Alice          | F    | 1986-04-05 | Daughter     |
-- | 333445555 | Joy            | F    | 1958-05-03 | Spouse       |
-- | 333445555 | Theodore       | M    | 1983-10-25 | Son          |
-- | 987654321 | Abner          | M    | 1942-02-28 | Spouse       |
-- +-----------+----------------+------+------------+--------------+
-- 7 rows in set (0.00 sec)