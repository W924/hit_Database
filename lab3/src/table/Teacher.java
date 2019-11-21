package table;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;
import java.sql.Statement;
import java.util.Scanner;
import com.mysql.cj.jdbc.exceptions.MysqlDataTruncation;

public class Teacher {

  private static final String DB_URL = "jdbc:mysql://localhost:3306/teaching_database?serverTimezone=GMT";
  private static final String USER = "root";
  private static final String PASS = "123456";
  
  public static void InsertTuple() {
    Connection conn = null;
    Statement stmt = null;
    @SuppressWarnings("resource")
    Scanner sc = new Scanner(System.in);
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      conn = DriverManager.getConnection(DB_URL,USER,PASS);
      stmt = conn.createStatement();
      
      System.out.print("teacher number: ");
      String tno = sc.nextLine();
      System.out.print("teacher name: ");
      String tname = sc.nextLine();
      System.out.print("sex: ");
      String tsex = sc.nextLine();
      System.out.print("birthday: ");
      String tbirth = sc.nextLine();
      System.out.print("title: ");
      String ttitle = sc.nextLine();
      System.out.print("home: ");
      String thome = sc.nextLine();
      System.out.print("fno: ");
      String fno = sc.nextLine();
      
      if(tno.equals("")) {
        System.out.println("Insert Error: teacher number can not be null!\n");
      } else if(tname.equals("")) {
        System.out.println("Insert Error: teacher name can not be null!\n");
      } else if(tsex.equals("")) {
        System.out.println("Insert Error: teacher sex can not be null!\n");
      } else if(tbirth.equals("")) {
        System.out.println("Insert Error: teacher birthday can not be null!\n");
      } else if(ttitle.equals("")) {
        System.out.println("Insert Error: teacher title can not be null!\n");
      } else if(thome.equals("")) {
        System.out.println("Insert Error: teacher home can not be null!\n");
      } else if(fno.equals("")) {
        System.out.println("Insert Error: faculty number can not be null!\n");
      } else {
        stmt.executeLargeUpdate("insert into teacher "
                              + "values('" + tno + "', '" + tname +  "', '" + tsex + "', '" + tbirth + "', '" + ttitle + "', '" + thome + "', '" + fno + "');");
        
        System.out.println("插入成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      String str = e.getMessage();
      if(str.contains("Duplicate entry")) {
        System.out.println("Insert Error: Primary key 'teacher number' has existed in this table!\n");
      }
      if(str.contains("foreign key constraint")) {
        System.out.println("Insert Error: Foreign key 'faculty number' don't exist in College table!\n");
      }
    } catch (SQLException se) {
      se.printStackTrace();
    } catch (ClassNotFoundException e) {
      e.printStackTrace();
    } finally {
      try {
        if (stmt != null)
          stmt.close();
      } catch (SQLException se2) {
      }
      try {
        if (conn != null)
          conn.close();
      } catch (SQLException se) {
        se.printStackTrace();
      }
    }
  }
  
  public static void DeleteTuple() {
    Connection conn = null;
    Statement stmt = null;
    @SuppressWarnings("resource")
    Scanner sc = new Scanner(System.in);
    try {
      Class.forName("com.mysql.cj.jdbc.Driver");
      conn = DriverManager.getConnection(DB_URL,USER,PASS);
      stmt = conn.createStatement();
      
      System.out.print("teacher number: ");
      String tno = sc.nextLine();
      
      if(tno.equals("")) {
        System.out.println("Delete Error: teacher number can not be null!\n");
      } else {
        stmt.executeLargeUpdate("delete from teacher "
                              + "where tno = '" + tno + "';");
        
        System.out.println("删除成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      System.out.println("Insert Error: 'teacher number' is foreign key of other table and the entered value has appeared in other table!\n");
    } catch (SQLException se) {
      se.printStackTrace();
    } catch (ClassNotFoundException e) {
      e.printStackTrace();
    } finally {
      try {
        if (stmt != null)
          stmt.close();
      } catch (SQLException se2) {
      }
      try {
        if (conn != null)
          conn.close();
      } catch (SQLException se) {
        se.printStackTrace();
      }
    }
  }
  
}
