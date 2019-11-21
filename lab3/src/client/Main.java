package client;

import java.util.Scanner;
import query.course_student;
import query.faculty_teacher;
import query.teacher_student;
import table.College;
import table.Course;
import table.Dorm;
import table.Faculty;
import table.SC;
import table.SD;
import table.SS;
import table.Society;
import table.Student;
import table.Teacher;
import table.Teaching;
import table.TeachingClass;

public class Main {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    while(true) {
      System.out.println("------------------------教学管理系统----------------------");
      System.out.println("1.插入数据");
      System.out.println("2.删除数据");
      System.out.println("3.常用查询");
      System.out.println("4.exit");
      System.out.println("选择你要进行的操作: ");
      String num = in.nextLine();
      if(num.equals("1")) {
        while(true) {
          System.out.println("输入所要插入的关系表的名称: ");
          String table_name = in.nextLine();
          switch (table_name.toLowerCase()) {
            case "college":
              College.InsertTuple();
              break;
            case "faculty":
              Faculty.InsertTuple();
              break;
            case "teacher":
              Teacher.InsertTuple();
              break;
            case "class":
              TeachingClass.InsertTuple();
              break;
            case "course":
              Course.InsertTuple();
              break;
            case "teaching":
              Teaching.InsertTuple();
              break;
            case "student":
              Student.InsertTuple();
              break;
            case "sc":
              SC.InsertTuple();
              break;
            case "dorm":
              Dorm.InsertTuple();
              break;
            case "sd":
              SD.InsertTuple();
              break;
            case "society":
              Society.InsertTuple();
              break;
            case "ss":
              SS.InsertTuple();
              break;
            default:
              System.out.println("Error: table name input error!\n");
          }
          try {
            Thread.sleep(10);
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
          System.out.print("是否要继续插入数据(yes/no): ");
          String str = in.nextLine();
          if(str.equals("no")) {
            break;
          } else if(str.equals("yes")) {
            continue;
          }
        }
      } else if(num.equals("2")) {
        while(true) {
          System.out.println("输入所要删除元组所在的的关系表的名称: ");
          String table_name = in.nextLine();
          switch (table_name.toLowerCase()) {
            case "college":
              College.DeleteTuple();
              break;
            case "faculty":
              Faculty.DeleteTuple();
              break;
            case "teacher":
              Teacher.DeleteTuple();
              break;
            case "class":
              TeachingClass.DeleteTuple();
              break;
            case "course":
              Course.DeleteTuple();
              break;
            case "teaching":
              Teaching.DeleteTuple();
              break;
            case "student":
              Student.DeleteTuple();
              break;
            case "sc":
              SC.DeleteTuple();
              break;
            case "dorm":
              Dorm.DeleteTuple();
              break;
            case "sd":
              SD.DeleteTuple();
              break;
            case "society":
              Society.DeleteTuple();
              break;
            case "ss":
              SS.DeleteTuple();
              break;
            default:
              System.out.println("Error: table name input error!\n");
          }
          try {
            Thread.sleep(10);
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
          System.out.print("是否要继续删除数据(yes/no): ");
          String str = in.nextLine();
          if(str.equals("no")) {
            break;
          } else if(str.equals("yes")) {
            continue;
          }
        }
      } else if(num.equals("3")) {
        while(true) {
          System.out.println("\n常用查询");
          System.out.println("1.查询选修过某门课的学生学号和姓名");
          System.out.println("2.查询某一系的教师的姓名和性别");
          System.out.println("3.没有选修过某课程的学生学号和姓名");
          System.out.println("4.查询某教师管理的班级的学生学号和姓名");
          System.out.println("5.查询至少选修了%N%门课的学生的学号");
          System.out.println("选择你要进行的查询: ");
          String query_number = in.nextLine();
          switch(query_number) {
            case "1":
              course_student.query1();
              break;
            case "2":
              faculty_teacher.query();
              break;
            case "3":
              course_student.query2();
              break;
            case "4":
              teacher_student.query();
              break;
            case "5":
              course_student.query3();
              break;
            default:
              System.out.println("查询类型输入错误!\n");
          }
          try {
            Thread.sleep(10);
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
          System.out.print("是否要继续进行查询(yes/no): ");
          String str = in.nextLine();
          if(str.equals("no")) {
            break;
          } else if(str.equals("yes")) {
            continue;
          }
        }
      } else if(num.equals("4")) {
        break;
      } else {
        System.out.println("输入错误！");
      }
    }
    in.close();
  }

}
