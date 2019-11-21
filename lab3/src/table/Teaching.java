package table;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;
import java.sql.Statement;
import java.util.Scanner;
import com.mysql.cj.jdbc.exceptions.MysqlDataTruncation;

public class Teaching {

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
      System.out.print("course number: ");
      String cno = sc.nextLine();
      System.out.print("course time: ");
      String time = sc.nextLine();
      
      if(tno.equals("")) {
        System.out.println("Insert Error: Primary key 'teacher number' can not be null!\n");
      } else if(cno.equals("")) {
        System.out.println("Insert Error: Primary key 'course number' can not be null!\n");
      } else if(time.equals("")) {
        System.out.println("Insert Error: Primary key 'course time' can not be null!\n");
      } else {
        stmt.executeLargeUpdate("insert into teaching "
                              + "values('" + tno + "', '" + cno +  "', '" + time + "');");
        
        System.out.println("插入成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      String str = e.getMessage();
      if(str.contains("Duplicate entry")) {
        System.out.println("Insert Error: Primary key has existed in this table!\n");
      }
      if(str.contains("foreign key constraint")) {
        System.out.println("Insert Error: Foreign key don't exist in other table!\n");
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
      System.out.print("course number: ");
      String cno = sc.nextLine();
      System.out.print("course time: ");
      String time = sc.nextLine();
      
      if(tno.equals("")) {
        System.out.println("Delete Error: teacher number can not be null!\n");
      } else if(cno.equals("")) {
        System.out.println("Delete Error: course number can not be null!\n");
      } else if(time.equals("")) {
        System.out.println("Delete Error: course time can not be null!\n");
      } else {
        stmt.executeLargeUpdate("delete from teaching "
                              + "where tno = '" + tno + "' and "
                              + "cno = '" + cno + "' and "
                              + "time = '" + time + "';");
        
        System.out.println("删除成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      System.out.println("Insert Error: the entered primary key has appeared in the foreign key of other tables.!\n");
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
