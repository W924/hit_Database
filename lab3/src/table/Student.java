package table;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;
import java.sql.Statement;
import java.util.Scanner;
import com.mysql.cj.jdbc.exceptions.MysqlDataTruncation;

public class Student {

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
      
      System.out.print("student number: ");
      String sno = sc.nextLine();
      System.out.print("student name: ");
      String sname = sc.nextLine();
      System.out.print("student sex: ");
      String ssex = sc.nextLine();
      System.out.print("student birthday: ");
      String sbirth = sc.nextLine();
      System.out.print("start year: ");
      String startyear = sc.nextLine();
      System.out.print("class number: ");
      String classno = sc.nextLine();
      
      if(sno.equals("")) {
        System.out.println("Insert Error: student number can not be null!\n");
      } else if(sname.equals("")) {
        System.out.println("Insert Error: student name can not be null!\n");
      } else if(ssex.equals("")) {
        System.out.println("Insert Error: student sex can not be null!\n");
      } else if(sbirth.equals("")) {
        System.out.println("Insert Error: student birthday can not be null!\n");
      } else if(startyear.equals("")) {
        System.out.println("Insert Error: student start year can not be null!\n");
      } else if(classno.equals("")) {
        System.out.println("Insert Error: class number of the student can not be null!\n");
      } else {
        stmt.executeLargeUpdate("insert into student "
                              + "values('" + sno + "', '" + sname + "', '" + ssex + "', '" + sbirth + "', '" + startyear +  "', '" + classno + "');");
        
        System.out.println("插入成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      String str = e.getMessage();
      if(str.contains("Duplicate entry")) {
        System.out.println("Insert Error: Primary key 'student number' has existed in this table!\n");
      }
      if(str.contains("foreign key constraint")) {
        System.out.println("Insert Error: Foreign key 'class number' don't exist in Class table!\n");
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
      
      System.out.print("student number: ");
      String sno = sc.nextLine();
      
      if(sno.equals("")) {
        System.out.println("Delete Error: student number can not be null!\n");
      } else {
        stmt.executeLargeUpdate("delete from student "
                              + "where sno = '" + sno + "';");
        
        System.out.println("删除成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      System.out.println("Insert Error: 'student number' is foreign key of other table and the entered value has appeared in other table!\n");
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
