package table;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;
import java.sql.Statement;
import java.util.Scanner;
import com.mysql.cj.jdbc.exceptions.MysqlDataTruncation;

public class TeachingClass {

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
      
      System.out.print("class number: ");
      String classno = sc.nextLine();
      System.out.print("faculty number: ");
      String fno = sc.nextLine();
      System.out.print("head teacher number: ");
      String tno = sc.nextLine();
      
      if(classno.equals("")) {
        System.out.println("Insert Error: class number can not be null!\n");
      } else if(fno.equals("")) {
        System.out.println("Insert Error: faculty number can not be null!\n");
      } else if(tno.equals("")) {
        System.out.println("Insert Error: teacher number can not be null!\n");
      } else {
        stmt.executeLargeUpdate("insert into class "
                              + "values('" + classno + "', '" + fno +  "', '" + tno + "');");
        
        System.out.println("插入成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      String str = e.getMessage();
      if(str.contains("Duplicate entry")) {
        System.out.println("Insert Error: Primary key 'class number' has existed in this table!\n");
      }
      if(str.contains("foreign key constraint")) {
        if(str.contains("fno")) {
          System.out.println("Insert Error: Foreign key 'faculty number' don't exist in Faculty table!\n");
        }
        if(str.contains("tno")) {
          System.out.println("Insert Error: Foreign key 'teacher number' don't exist in Teacher table!\n");
        }
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
      
      System.out.print("class number: ");
      String classno = sc.nextLine();
      
      if(classno.equals("")) {
        System.out.println("Delete Error: class number can not be null!\n");
      } else {
        stmt.executeLargeUpdate("delete from class "
                              + "where classno = '" + classno + "';");
        
        System.out.println("删除成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      System.out.println("Insert Error: 'class number' is foreign key of other table and the entered value has appeared in other table!\n");
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
