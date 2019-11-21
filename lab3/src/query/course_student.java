package query;

import java.sql.Connection;
import java.sql.Driver;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;
import java.util.Scanner;

public class course_student {

  private static final String DB_URL = "jdbc:mysql://localhost:3306/teaching_database?serverTimezone=GMT";
  private static final String USER = "root";
  private static final String PASS = "123456";
  
  public static void query1() {
    Connection conn = null;
    Statement stmt = null;
    @SuppressWarnings("resource")
    Scanner sc = new Scanner(System.in);
    try{
      
      Driver driver = new com.mysql.cj.jdbc.Driver();
      Properties props = new Properties();
      props.setProperty("user", USER);
      props.setProperty("password", PASS);
      conn = driver.connect(DB_URL, props);
      stmt = conn.createStatement();
      ResultSet rs = null;
      
      System.out.println("course number: ");
      String cno = sc.nextLine();
      
      String sql1 = "select student.sno, student.sname "
                  + "from student, sc "
                  + "where sc.cno = '" + cno + "' and "
                  + "sc.sno = student.sno";
      rs = stmt.executeQuery(sql1);
      System.out.println("选修过课程编号为" + cno + "的学生学号和姓名");
      System.out.println("------------------------------------------");
      System.out.println("sno   sname");
      while(rs.next()){
        String sno = rs.getString("sno");
        String sname = rs.getString("sname");
        System.out.println(sno + "\t" + sname);
      }
      System.out.println("------------------------------------------\n"); 

      rs.close();
      stmt.close();
      conn.close();
  }catch(SQLException se){
      se.printStackTrace();
  }catch(Exception e){
      e.printStackTrace();
  }finally{
      try{
          if(stmt!=null) stmt.close();
      }catch(SQLException se2){
      }
      try{
          if(conn!=null) conn.close();
      }catch(SQLException se){
          se.printStackTrace();
      }
    }
  }
  
  public static void query2() {
    Connection conn = null;
    Statement stmt = null;
    @SuppressWarnings("resource")
    Scanner sc = new Scanner(System.in);
    try{
      
      Driver driver = new com.mysql.cj.jdbc.Driver();
      Properties props = new Properties();
      props.setProperty("user", USER);
      props.setProperty("password", PASS);
      conn = driver.connect(DB_URL, props);
      stmt = conn.createStatement();
      ResultSet rs = null;
      
      System.out.println("course number: ");
      String cno = sc.nextLine();
      
      String sql1 = "select sno, sname "
                  + "from student "
                  + "where sno not in( "
                  + "select sno "
                  + "from sc "
                  + "where cno = '" + cno + "')";
      rs = stmt.executeQuery(sql1);
      System.out.println("没有选修过课程编号为" + cno + "的学生学号和姓名");
      System.out.println("------------------------------------------");
      System.out.println("sno   sname");
      while(rs.next()){
        String sno = rs.getString("sno");
        String sname = rs.getString("sname");
        System.out.println(sno + "\t" + sname);
      }
      System.out.println("------------------------------------------\n"); 

      rs.close();
      stmt.close();
      conn.close();
  }catch(SQLException se){
      se.printStackTrace();
  }catch(Exception e){
      e.printStackTrace();
  }finally{
      try{
          if(stmt!=null) stmt.close();
      }catch(SQLException se2){
      }
      try{
          if(conn!=null) conn.close();
      }catch(SQLException se){
          se.printStackTrace();
      }
    }
  }
  
  public static void query3() {
    Connection conn = null;
    Statement stmt = null;
    @SuppressWarnings("resource")
    Scanner sc = new Scanner(System.in);
    try{
      
      Driver driver = new com.mysql.cj.jdbc.Driver();
      Properties props = new Properties();
      props.setProperty("user", USER);
      props.setProperty("password", PASS);
      conn = driver.connect(DB_URL, props);
      stmt = conn.createStatement();
      ResultSet rs = null;
      
      System.out.println("选修课程的数目: ");
      String number = sc.nextLine();
      
      String sql1 = "select sno "
                  + "from sc "
                  + "group by sno "
                  + "having count(*) >= '" + number + "';";
      rs = stmt.executeQuery(sql1);
      System.out.println("至少选修了" + number + "门课的学生学号和姓名");
      System.out.println("------------------------------------------");
      System.out.println("sno");
      while(rs.next()){
        String sno = rs.getString("sno");
        System.out.println(sno);
      }
      System.out.println("------------------------------------------\n"); 

      rs.close();
      stmt.close();
      conn.close();
  }catch(SQLException se){
      se.printStackTrace();
  }catch(Exception e){
      e.printStackTrace();
  }finally{
      try{
          if(stmt!=null) stmt.close();
      }catch(SQLException se2){
      }
      try{
          if(conn!=null) conn.close();
      }catch(SQLException se){
          se.printStackTrace();
      }
    }
  }
  
}
