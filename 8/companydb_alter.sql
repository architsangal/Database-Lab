alter table employee
    ADD CONSTRAINT fk_super_ssn FOREIGN KEY (super_ssn)
REFERENCES employee(ssn);

alter table employee
    ADD CONSTRAINT fk_dno FOREIGN KEY (dno)
REFERENCES department(dnumber);

alter table department
    ADD CONSTRAINT fk_mgr_ssn FOREIGN KEY (mgr_ssn)
REFERENCES employee(ssn);

alter table dept_locations
    ADD CONSTRAINT fk_dnumber FOREIGN KEY (dnumber)
REFERENCES department(dnumber);

alter table project
    ADD CONSTRAINT fk_dnum FOREIGN KEY (dnum)
REFERENCES department(dnumber);

alter table works_on
    ADD CONSTRAINT fk_essn FOREIGN KEY (essn)
REFERENCES employee(ssn);

alter table works_on
    ADD CONSTRAINT fk_pno FOREIGN KEY (pno)
REFERENCES project(pnumber);

alter table table_dependent
    ADD CONSTRAINT fk_dependent_essn FOREIGN KEY (essn)
REFERENCES employee(ssn);