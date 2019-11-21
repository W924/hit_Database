package table;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;
import java.sql.Statement;
import java.util.Scanner;
import com.mysql.cj.jdbc.exceptions.MysqlDataTruncation;

public class SD {

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
      System.out.print("dorm number: ");
      String dno = sc.nextLine();
      
      if(dno.equals("")) {
        System.out.println("Insert Error: dorm number can not be null!\n");
      } else if(sno.equals("")) {
        System.out.println("Insert Error: student number can not be null!\n");
      } else {
        stmt.executeLargeUpdate("insert into sd "
                              + "values('" + sno + "', '" + dno + "');");
        
        System.out.println("����ɹ�!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      String str = e.getMessage();
      if(str.contains("Duplicate entry")) {
        System.out.println("Insert Error: Primary key has existed in this table!\n");
      }
      if(str.contains("foreign key constraint")) {
        System.out.println("Insert Error: Foreign key don't exist in other tables!\n");
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
      System.out.print("dorm number: ");
      String dno = sc.nextLine();
      
      if(sno.equals("")) {
        System.out.println("Delete Error: student number can not be null!\n");
      } else if(dno.equals("")) {
        System.out.println("Delete Error: dorm number can not be null!\n");
      } else {
        stmt.executeLargeUpdate("delete from sd "
                              + "where sno = '" + sno + "' and "
                              + "dno = '" + dno + "';");
        
        System.out.println("ɾ���ɹ�!\n ");
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
