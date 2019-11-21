package query;

import java.sql.Connection;
import java.sql.Driver;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Properties;
import java.util.Scanner;

public class teacher_student {

  private static final String DB_URL = "jdbc:mysql://localhost:3306/teaching_database?serverTimezone=GMT";
  private static final String USER = "root";
  private static final String PASS = "123456";
  
  public static void query() {
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
      
      System.out.println("teacher number: ");
      String tno = sc.nextLine();
      
      String sql1 = "select student.sno, student.sname "
                  + "from student, class "
                  + "where class.tno = '" + tno + "' and "
                  + "class.classno = student.classno";
      rs = stmt.executeQuery(sql1);
      System.out.println("由教师编号为" + tno + "所管理班级的学生学号和姓名");
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
}
