package table;

import java.sql.*;
import java.util.Scanner;
import com.mysql.cj.jdbc.exceptions.MysqlDataTruncation;

public class College {

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
      
      System.out.print("college number: ");
      String collegeno = sc.nextLine();
      System.out.print("college name: ");
      String collegename = sc.nextLine();
      
      if(collegeno.equals("")) {
        System.out.println("Insert Error: college number can not be null!\n");
      } else if(collegename.equals("")) {
        System.out.println("Insert Error: college name can not be null!\n");
      } else {
        stmt.executeLargeUpdate("insert into college "
                              + "values('" + collegeno + "', '" + collegename +  "');");
        
        System.out.println("插入成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      System.out.println("Insert Error: Primary key 'college number' has exist in this table!\n");
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
      
      System.out.print("college number: ");
      String collegeno = sc.nextLine();
      
      if(collegeno.equals("")) {
        System.out.println("Delete Error: college number can not be null!\n");
      } else {
        stmt.executeLargeUpdate("delete from college "
                              + "where collegeno = '" + collegeno + "';");
        
        System.out.println("删除成功!\n ");
      }
    } catch (MysqlDataTruncation e) {
      System.out.println("Insert Error: Date too long for the property!\n");
    } catch (SQLIntegrityConstraintViolationException e) {
      System.out.println("Insert Error: 'college number' is foreign key of other table and the entered value has appeared in other table!\n");
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
