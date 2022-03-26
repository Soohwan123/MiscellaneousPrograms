using System;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HelpdeskDAL;
using Xunit;

namespace CasestudyTest
{
    public class LinqTests
    {
        [Fact]
        public void Test1()
        {
            HelpdeskContext _db = new HelpdeskContext();

            var selectedEmployees = from stu in _db.Employees
                                   where stu.Id == 2
                                   select stu;

            int stus = selectedEmployees.Count();

            Assert.True(selectedEmployees.Count() > 0);
        }

        [Fact]
        public void Test2()
        {
            HelpdeskContext _db = new HelpdeskContext();

            var selectedEmployees = from stu in _db.Employees
                                   where stu.Title == "Ms." || stu.Title == "Mrs."
                                   select stu;

            Assert.True(selectedEmployees.Count() > 0);
        }

        [Fact]
        public void Test3()
        {
            HelpdeskContext _db = new HelpdeskContext();

            var selectedEmployees = from stu in _db.Employees
                                   where stu.Department.Id == 500
                                   select stu;


            Assert.True(selectedEmployees.Count() > 0);
        }

        //same as Test1
        [Fact]
        public void Test4()
        {
            HelpdeskContext _db = new HelpdeskContext();

            //FirstOrDefault : return the first of the database or just returns NULL
            Employee selectEmployee = _db.Employees.FirstOrDefault(
                stu =>
                stu.Id == 9
                );

            Assert.True(selectEmployee.FirstName == "Mopn");
        }


        //same as Test2
        [Fact]
        public void Test5()
        {
            HelpdeskContext _db = new HelpdeskContext();

            //FirstOrDefault : return the first of the database or just returns NULL
            var selectEmployee = _db.Employees.Where(
                stu =>
                stu.Title == "Ms." || stu.Title == "Mrs."
                );

            Assert.True(selectEmployee.Count() > 0);
        }

        [Fact]
        public void Test6()
        {
            HelpdeskContext _db = new HelpdeskContext();

            var selectedEmployees = _db.Employees.Where(
                stu =>
                stu.Department.DepartmentName == "Maintenance"
                );
            var firstStu = selectedEmployees.FirstOrDefault();

            Assert.True(selectedEmployees.Count() > 0);
        }

        [Fact]
        public async Task Test7()
        {
            HelpdeskContext _db = new HelpdeskContext();

            Employee selectedEmployee = await _db.Employees.FirstOrDefaultAsync(stu => stu.Id == 9);

            if (selectedEmployee != null)
            {
                string currentEmail = selectedEmployee.Email;
                string newEmail = currentEmail == "td@abc.com" ? "sk@abc.com" : "td@abc.com";  //if currentPhoneNo is "519-555-1234" -> change to "555-555-5555", otherwise change to "519-555-1234" 

                selectedEmployee.Email = newEmail;
                _db.Entry(selectedEmployee).CurrentValues.SetValues(selectedEmployee);                    // Entry -> get the entity SetValues -> override the phone number to the number that we just changed
            }

            Assert.True(await _db.SaveChangesAsync() == 1);                                             // This is why we use asny in case of there's too many datas ( SaveChangesAsync -> boolean ) 1 is good, 0 nothing is changed
        }


        //Adding
        [Fact]
        public async Task Test8()
        {
            HelpdeskContext _db = new HelpdeskContext();
            Employee newEmployee = new Employee();
            newEmployee.FirstName = "Soohwan";
            newEmployee.LastName = "Kim";
            newEmployee.PhoneNo = "(555)555-1234";
            newEmployee.Title = "Mr.";
            newEmployee.DepartmentId = 500;
            newEmployee.Email = "sc@sc.com";
            await _db.Employees.AddAsync(newEmployee);
            await _db.SaveChangesAsync();
            Assert.True(newEmployee.Id > 1);
        }

        [Fact]
        public async Task Test9()
        {
            HelpdeskContext _db = new HelpdeskContext();
            Employee selectedEmployee = await _db.Employees.FirstOrDefaultAsync(stu => stu.FirstName == "Soohwan");
            if (selectedEmployee != null)
            {
                _db.Employees.Remove(selectedEmployee);
                Assert.True(await _db.SaveChangesAsync() == 1);
            }
            else
            {
                Assert.True(false);
            }
        }
    }
}
