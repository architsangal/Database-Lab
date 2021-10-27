alter table employee
    DROP FOREIGN KEY fk_super_ssn;

alter table employee
    DROP FOREIGN KEY fk_dno;

alter table department
    DROP FOREIGN KEY fk_mgr_ssn;

alter table dept_locations
    DROP FOREIGN KEY fk_dnumber;

alter table project
    DROP FOREIGN KEY fk_dnum;

alter table works_on
    DROP FOREIGN KEY fk_essn;

alter table works_on
    DROP FOREIGN KEY fk_pno;

alter table table_dependent
    DROP FOREIGN KEY fk_dependent_essn;

-- used show tables;
drop table department;
drop table dept_locations;
drop table employee;
drop table project;
drop table table_dependent;
drop table works_on;