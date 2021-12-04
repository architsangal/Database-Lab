alter table student
    DROP FOREIGN KEY fk_book_id;

alter table book
    DROP FOREIGN KEY fk_student_rno;

alter table book
    DROP FOREIGN KEY fk_admin_roll_number;

drop table book;
drop table library_manager;
drop table student;

drop database library;