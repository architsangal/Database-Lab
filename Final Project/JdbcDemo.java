import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.*;
public class JdbcDemo
{
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
    static final String DB_URL = "jdbc:mysql://localhost/library?allowPublicKeyRetrieval=true&useSSL=false";
    static final String USER = "user45";
    static final String PASS = "Password@45";

    static String mag_id;
    static String mag_name;
    static int books_available;

    public static void main(String[] args)throws IOException
    {
        Connection conn = null;
        Statement stmt = null;

        try
        {
            Class.forName(JDBC_DRIVER);
            InputStreamReader in = new InputStreamReader(System.in);
            BufferedReader br = new BufferedReader(in);
            System.out.print("\nWant to continue? [Y/N]:");
            String input = br.readLine();
            if(input.equals("N")||input.equals("n"))
            {
                System.exit(0);
            }
            clear();
    
            conn = DriverManager.getConnection(DB_URL,USER,PASS);
            stmt = conn.createStatement();

            println("\n\n\n\n			Hello User !!\n");

            choice(stmt, br);

            br.close();
            in.close();
            stmt.close();
            conn.close();
        }
        catch(SQLException se)
        {
            se.printStackTrace();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        finally
        {
            try
            {
                if(stmt!=null)
                    stmt.close();
                if(conn!=null)
                    conn.close();
            }
            catch(SQLException se)
            {
                se.printStackTrace();
            }
        }
    }

    static void choice(Statement stmt,BufferedReader br)throws IOException, SQLException
    {
        println("Login As - ");
        println("1. Student");
        println("2. Library Manager");
        println("3. Exit");

        print("Enter Your Choice: ");
        int input = Integer.parseInt(br.readLine());
        clear();

        if(input == 1)
            student_choice(stmt,br);
        else if(input == 2)
            manager_choice(stmt,br);
        else
            System.exit(0);
        choice(stmt, br);
    }

    static void student_choice(Statement stmt,BufferedReader br)throws IOException
    {
        System.out.println("\n\n\n\n\n\n");

        println("Choice from the available options- ");
        println("1. List of available books");
        println("2. Exit");
        print("Enter your choice: ");
        int input = Integer.parseInt(br.readLine());
        clear();

        if(input == 1)
            list_of_books(stmt, br);
        else if(input == 2)
            return;
        student_choice(stmt, br);
    }

    static void list_of_books(Statement stmt,BufferedReader br) throws IOException
    {
        clear();
        String books = "select * from book";
        ResultSet rs = executeSqlCommand(books, stmt);
        
        try
        {
            println("List of Available books:\n");
            int f=0;
            while(rs.next())
            {
                //Retrieve by column name
                String id  = rs.getString("book_id");
                String name = rs.getString("book_name");
                String author = rs.getString("book_name");
                String student_rno = rs.getString("student_rno");
                String admin_roll_number = rs.getString("admin_roll_number");
            
                if(student_rno == null || admin_roll_number == null)
                {
                    f=1;
                    //Display values
                    println("Book ID  : " + id);
                    println("Book Name: " + name);
                    println("Author : " + author);
                    println("");
                }
            }

            if(f==0)
            {
                println("Sorry, but no books are available");
                books_available = 0;
            }
            else
            {
                books_available = 1;
            }

            //STEP 5: Clean-up environment
            rs.close();
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }
    }
    
    static boolean verify_manager(Statement stmt,BufferedReader br) throws IOException, SQLException
    {
        System.out.println("\n\n\n\n\n\n");
        print("Enter ID: ");
        String id = br.readLine();
        print("Enter Password: ");
        String password = br.readLine();

        clear();

        String name = null;

        String managers = "select * from library_manager";
        ResultSet rs = executeSqlCommand(managers, stmt);

        int f=0;
        while(rs.next())
        {
            //Retrieve by column name
            String possible_id  = rs.getString("admin_number");
            String given_name = rs.getString("admin_name");
            String possible_password = rs.getString("password_admin");
        
            if(possible_id.equals(id) && password.equals(possible_password))
            {
                f=1;
                name = given_name;
                break;
            }
        }

        if(f==1)
        {
            mag_id = id;
            mag_name = name;
            return true;
        }
        else
            return false;
    }
    
    static void manager_choice(Statement stmt,BufferedReader br) throws IOException, SQLException
    {
        if(verify_manager(stmt,br))
        {
            manager_choices(stmt, br);
        }
        else
        {
            System.out.println("\n\n\n\n\n\n");
            println("Entered Details were incorrect. Please try again.");
            manager_choice(stmt, br);
            return;
        }
    }
    
    static void manager_choices(Statement stmt,BufferedReader br) throws IOException, SQLException
    {
        System.out.println("\n\n\n\n\n\n");

        println("Choice from the available options- ");
        println("1.  List of available books");
        println("2.  Issue a book");
        println("3.  Return a book");
        println("4.  Add a student");
        println("5.  Add a library manager");
        println("6.  Add a book");
        println("7.  Delete a book");
        println("8.  Delete a student account");
        println("9.  Delete your account");
        println("10. List of all books");
        println("0. Log Out");
        print("Enter your choice: ");
        int input = Integer.parseInt(br.readLine());
        clear();

        if(input == 1)
            list_of_books(stmt, br);
        else if(input == 2)
            issue_a_book(stmt, br);
        else if(input == 3)
            return_a_book(stmt, br);
        else if(input == 4)
            add_a_student(stmt,br);
        else if(input == 5)
            add_a_manager(stmt,br);
        else if(input == 6)
            add_a_book(stmt,br);
        else if(input == 7)
            delete_a_book(stmt,br);
        else if(input == 8)
            delete_a_student(stmt,br);
        else if(input == 9)
        {
            delete_a_manager(stmt,br);
            return;
        }
        else if(input == 10)
            list_of_books2(stmt, br);
        else if(input == 0)
            return;
        manager_choices(stmt, br);
    }

    static void list_of_books2(Statement stmt,BufferedReader br) throws IOException
    {
        clear();
        String books = "select * from book";
        ResultSet rs = executeSqlCommand(books, stmt);
        
        try
        {
            println("List of Available books:\n");
            int f=0;
            while(rs.next())
            {
                f=1;
                //Retrieve by column name
                String id  = rs.getString("book_id");
                String name = rs.getString("book_name");
                String author = rs.getString("book_name");
                String student_rno = rs.getString("student_rno");
                String admin_roll_number = rs.getString("admin_roll_number");
            
                //Display values
                println("Book ID  : " + id);
                println("Book Name: " + name);
                println("Author : " + author);
                println("Student Roll No. : " + student_rno);
                println("Admin Number : " + admin_roll_number);
                println("");
            }

            if(f==0)
            {
                println("Sorry, but no books were found");
            }

            //STEP 5: Clean-up environment
            rs.close();
        }
        catch(SQLException e)
        {
            e.printStackTrace();
        }
    }


    private static void delete_a_manager(Statement stmt, BufferedReader br)
    {
        try
        {
            String managers = "DELETE FROM library_manager where admin_number = \'"+ mag_id+"\'";
            int result = updateSqlCommand(managers, stmt);

            if(result != 0)
                println("Student Account Deleted!");
            else
                println("Something went wrong!");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    private static void delete_a_student(Statement stmt, BufferedReader br)
    {
        try
        {
            print("Enter the ID of the student: ");
            String id = br.readLine();

            clear();

            String managers = "DELETE FROM student where student_roll_number = \'"+ id+"\'";
            int result = updateSqlCommand(managers, stmt);

            if(result != 0)
                println("Student Account Deleted!");
            else
                println("Something went wrong!");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    private static void delete_a_book(Statement stmt, BufferedReader br)
    {
        try
        {
            print("Enter the ID of the book: ");
            String id = br.readLine();

            clear();

            String managers = "DELETE FROM book where book_id = \'"+ id+"\'";
            int result = updateSqlCommand(managers, stmt);

            if(result != 0)
                println("Book Deleted!");
            else
                println("Something went wrong!");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }

    }

    static void issue_a_book(Statement stmt,BufferedReader br) throws IOException, SQLException
    {
        try
        {
            list_of_books(stmt, br);
            if(books_available==0)
            {
                println("Sorry, but no books are available");
            }
            else
            {

                print("Enter the ID of the book: ");
                String id = br.readLine();

                print("Enter the id of the student: ");
                String student_id = br.readLine();

                clear();

                String managers = "UPDATE book SET student_rno = \'"+ student_id +"\', admin_roll_number = \'"+mag_id+"\' where book_id = \'"+id+"\'";
                int result = updateSqlCommand(managers, stmt);

                managers = "UPDATE student SET book_id = \'"+ id +"\' where student_roll_number = \'"+student_id+"\'";
                int result2 = updateSqlCommand(managers, stmt);

                if(result != 0 && result2 != 0)
                    println("Book Issued!");
                else
                    println("Something went wrong!");
            }
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    static void return_a_book(Statement stmt,BufferedReader br) throws IOException
    {
        try
        {
            print("Enter the ID of the book: ");
            String id = br.readLine();

            print("Enter the id of the student: ");
            String student_id = br.readLine();

            clear();

            String managers = "UPDATE book SET student_rno = null, admin_roll_number = null where book_id = \'"+id+"\'";
            int result = updateSqlCommand(managers, stmt);

            managers = "UPDATE student SET book_id = null where student_roll_number = \'"+student_id+"\'";
            int result2 = updateSqlCommand(managers, stmt);

            if(result != 0 && result2 != 0)
                println("Thank you for returning the book!");
            else
                println("Something went wrong!");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }

    }

    static void add_a_student(Statement stmt,BufferedReader br) throws IOException
    {
        try
        {
            print("Enter the ID of the student: ");
            String id = br.readLine();
            print("Enter the name of the student: ");
            String name = br.readLine();

            clear();

            String managers = "insert into student(student_roll_number,student_full_name,book_id) VALUES(\'"+id+"\',\'"+name+"\',NULL)";
            int result = updateSqlCommand(managers, stmt);

            if(result != 0)
                println("Student Info Added");
            else
                println("Something went wrong!");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }    

    static void add_a_book(Statement stmt,BufferedReader br) throws IOException
    {
        try
        {
            print("Enter the ID of book: ");
            String id = br.readLine();
            print("Enter the name of the book: ");
            String name = br.readLine();
            print("Enter the author of the book: ");
            String author = br.readLine();

            clear();

            String managers = "insert into book(book_id,book_name,book_author,student_rno,admin_roll_number)"+
            " VALUES(\'"+id+"\',\'"+name+"\',\'"+author+"\',NULL,NULL)";
            int result = updateSqlCommand(managers, stmt);

            if(result != 0)
                println("Booked Added");
            else
                println("Something went wrong!");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }    


    static void add_a_manager(Statement stmt,BufferedReader br) throws IOException
    {
        try
        {
            print("Enter the ID of the manager: ");
            String id = br.readLine();
            print("Enter the name of the manager: ");
            String name = br.readLine();
            print("Enter the password: ");
            String password = br.readLine();

            clear();

            String managers = "insert into library_manager(admin_number,admin_name,password_admin) VALUES(\'"+id+"\',\'"+name+"\',\'"+password+"\')";
            int result = updateSqlCommand(managers, stmt);

            if(result != 0)
                println("Library Manager Info Added");
            else
                println("Something went wrong!");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    
    static void clear()
    {
        System.out.print("\033[H\033[2J");
        System.out.flush();

    }

    static ResultSet executeSqlCommand(String sql, Statement stmt)
    {
        try
        {
            //STEP 3: Query to database
            ResultSet rs = stmt.executeQuery(sql);

            return rs;
            //STEP 4: Extract data from result set

        }
        catch(SQLException se)
        {
            se.printStackTrace();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return null;
    }
    
    static int updateSqlCommand(String sql, Statement stmt) throws SQLException
    {
        int result = stmt.executeUpdate(sql);
        return result;
    }
    
    static void println(String s)
    {
        System.out.println("                               "+s);
    }
    
    static void print(String s)
    {
        System.out.print("                                 "+s);
    }

}