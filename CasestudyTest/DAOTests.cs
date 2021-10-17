using System;
using Xunit;
using HelpdeskDAL;
using System.Diagnostics;
using System.Collections.Generic;
using System.Threading.Tasks;
namespace CasestudyTests
{
    public class DAOTests
    {
        [Fact]
        public async Task Employee_GetByEmailTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            Employee selectedEmployee = await dao.GetbyEmail("bs@abc.com");
            Assert.NotNull(selectedEmployee);
        }
        [Fact]
        public async Task Employee_GetByIdTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            Employee selectedEmployee = await dao.GetById(2);
            Assert.NotNull(selectedEmployee);
        }

        [Fact]
        public async Task Employee_GetAllTest()
        {
            EmployeeDAO dao = new HelpdeskDAL.EmployeeDAO();
            List<Employee> allEmployees = await dao.GetAll();
            Assert.NotNull(allEmployees);
        }

        [Fact]
        public async Task Employee_AddTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Employee newEmployees = new Employee();
            newEmployees.FirstName = "Soohwan";
            newEmployees.LastName = "Kim";
            newEmployees.PhoneNo = "(555)555-12343";
            newEmployees.Title = "Mr.";
            newEmployees.DepartmentId = 500;
            newEmployees.Email = "sc@sc.com";
            await dao.Add(newEmployees);
            Assert.True(newEmployees.Id > 0);
        }

        [Fact]
        public async Task Employee_UpdateTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Employee employeeForUpdate = await dao.GetById(1);
            if (employeeForUpdate != null)
            {
                string oldPhoneNo = employeeForUpdate.PhoneNo;
                string newPhoneNo = oldPhoneNo == "(555) 555-5551" ? "555-555-5555" : "(555) 555-5551";
                employeeForUpdate.PhoneNo = newPhoneNo;
            }
            Assert.True(await dao.Update(employeeForUpdate) == UpdateStatus.Ok);
        }

        [Fact]
        public async Task Employee_DeleteTest()
        {
            EmployeeDAO dao = new EmployeeDAO();
            Assert.True(await dao.Delete(8) == 1);
        }

        [Fact]
        public async Task Employee_ConcurrencyTest()
        {
            EmployeeDAO dao1 = new EmployeeDAO();
            EmployeeDAO dao2 = new EmployeeDAO();
            Employee employeeForUpdate1 = await dao1.GetById(1);
            Employee employeeForUpdate2 = await dao2.GetById(1);

            if (employeeForUpdate1 != null)
            {
                string oldPhoneNo = employeeForUpdate1.PhoneNo;
                string newPhoneNo = oldPhoneNo == "(555)555-1234" ? "555-555-5555" : "(555)555-1234";
                employeeForUpdate1.PhoneNo = newPhoneNo;
                if (await dao1.Update(employeeForUpdate1) == UpdateStatus.Ok)
                {
                    //need to change the phone # to something else
                    employeeForUpdate2.PhoneNo = "666-666-6666";
                    Assert.True(await dao2.Update(employeeForUpdate2) == UpdateStatus.Stale);
                }
                else
                    Assert.True(false);
            }
        }
    }

}